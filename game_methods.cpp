#include "vars.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <vector>

void start_game(){
    game_state.last_score = game_state.score;
    r = x; g = y; b = z;
    game_state.speed_last = game_state.speed;
}

int get_random_empty_cell(){
    int empty_cell_count = 0;
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            if (game_state.field[j][i] == FIELD_CELL_TYPE_NONE) {
                empty_cell_count++;
            }
        }
    }

    if (empty_cell_count == 0) {
        empty_cell_count = 1;
    }

    int target_empty_cell_index = rand() % empty_cell_count;
    int empty_cell_index = 0;

    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            if (game_state.field[j][i] == FIELD_CELL_TYPE_NONE) {
                if (empty_cell_index == target_empty_cell_index) {
                    return j * field_size_x + i;
                }
                empty_cell_index++;
            }
        }
    }

    return -1;
}

void add_apple(){
    int apple_pos = get_random_empty_cell();
    if (apple_pos != -1) {
        game_state.field[apple_pos / field_size_x][apple_pos % field_size_x] = FIELD_CELL_TYPE_APPLE;
    }
}

void add_green_apple(){
    int green_apple_pos = get_random_empty_cell();
    if (green_apple_pos != -1) {
        game_state.field[green_apple_pos / field_size_x][green_apple_pos % field_size_x] = FIELD_CELL_TYPE_GREEN_APPLE;
    }
}

void add_heart(){
    int heart_pos = get_random_empty_cell();
    if (heart_pos != -1) {
        game_state.field[heart_pos / field_size_x][heart_pos % field_size_x] = FIELD_CELL_TYPE_HEART;
    }
}


void add_yellow_apple(){
    int yellow_apple_pos = get_random_empty_cell();
    if (yellow_apple_pos != -1) {
        game_state.field[yellow_apple_pos / field_size_x][yellow_apple_pos % field_size_x] = FIELD_CELL_TYPE_YELLOW_APPLE;
    }
}


void clear_field(){
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            game_state.field[j][i] = FIELD_CELL_TYPE_NONE;
        }
    }

    for (int i = 0; i < game_state.snake_length; i++)
        game_state.field[game_state.snake_position_y][game_state.snake_position_x - i] = game_state.snake_length - i;
    switch(game_level){
        case 0:
            for (int i = 0; i < field_size_x; i++) {
                if (i<10||field_size_x-i - 1<10){
                    game_state.field[0][i]=FIELD_CELL_TYPE_WALL;
                    game_state.field[field_size_y - 1][i]=FIELD_CELL_TYPE_WALL;
                }
            }
            for (int j = 0; j < field_size_y - 1; j++) {
                if (j<5 || field_size_y-j - 1 < 5 ){
                    game_state.field[j][0]=FIELD_CELL_TYPE_WALL;
                    game_state.field[j][field_size_x - 1]=FIELD_CELL_TYPE_WALL;
                }
            }
            break;
    }

    add_apple();
    add_green_apple();
}

void grow_snake(){
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            if(game_state.field[j][i]>FIELD_CELL_TYPE_NONE){
                game_state.field[j][i]++;
            }
        }
    }
}

void draw_field(sf::RenderWindow& window){

    sf::Texture none_texture;
    none_texture.loadFromFile("images/none.png");
    sf::Sprite none;
    none.setTexture(none_texture);

    sf::Texture apple_texture;
    apple_texture.loadFromFile("images/apple.png");
    sf::Sprite apple;
    apple.setTexture(apple_texture);

    sf::Texture green_apple_texture;
    green_apple_texture.loadFromFile("images/apple_green.png");
    sf::Sprite green_apple;
    green_apple.setTexture(green_apple_texture);

    sf::Texture snake_texture;
    snake_texture.loadFromFile("images/snake.png");
    sf::Sprite snake;
    snake.setTexture(snake_texture);

    sf::Texture head_texture;
    head_texture.loadFromFile("images/head.png");
    sf::Sprite head;
    head.setTexture(head_texture);

    sf::Texture wall_texture;
    wall_texture.loadFromFile("images/wall.png");
    sf::Sprite wall;
    wall.setTexture(wall_texture);

    sf::Texture heart_texture;
    heart_texture.loadFromFile("images/life.png");
    sf::Sprite heart;
    heart.setTexture(heart_texture);

    sf::Texture yellow_apple_texture;
    yellow_apple_texture.loadFromFile("images/yelow_apple.png");
    sf::Sprite yellow_apple;
    yellow_apple.setTexture(yellow_apple_texture);

    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            switch (game_state.field[j][i]) {
                case FIELD_CELL_TYPE_NONE:
                    none.setPosition(float(i * cell_size), float(j * cell_size));
                    window.draw(none);
                    break;
                case FIELD_CELL_TYPE_APPLE:
                    apple.setPosition(float(i * cell_size), float(j * cell_size));
                    window.draw(apple);
                    break;
                case FIELD_CELL_TYPE_WALL:
                    wall.setPosition(float(i * cell_size), float(j * cell_size));
                    window.draw(wall);
                    break;
                case FIELD_CELL_TYPE_GREEN_APPLE:
                    green_apple.setPosition(float(i * cell_size), float(j * cell_size));
                    window.draw(green_apple);
                    break;
                case FIELD_CELL_TYPE_HEART:
                    heart.setPosition(float(i * cell_size), float(j * cell_size));
                    window.draw(heart);
                    break;
                case FIELD_CELL_TYPE_YELLOW_APPLE:
                    yellow_apple.setPosition(float(i * cell_size), float(j * cell_size));
                    window.draw(yellow_apple);
                    break;
                default:
                    if(game_state.field[j][i]==game_state.snake_length){
                        float offset_x=head.getLocalBounds().width/2;
                        float offset_y=head.getLocalBounds().height/2;
                        head.setPosition(float (i*cell_size+offset_x), float(j*cell_size+offset_y));
                        head.setOrigin(offset_x,offset_y);
                        switch (game_state.snake_direction) {
                            case SNAKE_DIRECTION_RIGHT:
                            head.setRotation(90);
                            break;
                            case SNAKE_DIRECTION_LEFT:
                                head.setRotation(-90);
                                break;
                            case SNAKE_DIRECTION_DOWN:
                                head.setRotation(180);
                                break;
                            case SNAKE_DIRECTION_UP:
                                head.setRotation(0);
                                break;
                        }

                        window.draw(head);
                    }
                    else{
                        snake.setPosition(float (i*cell_size), float(j*cell_size));
                        window.draw(snake);
                        break;
                    }
            }
        }
    }
}

void game_control(sf::RenderWindow& window){
    sf::Event event;
    if(!invert_control) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                int snake_direction_last = snake_direction_queue.empty() ? game_state.snake_direction
                                                                         : snake_direction_queue.at(0);
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        if (snake_direction_last != SNAKE_DIRECTION_UP &&
                            snake_direction_last != SNAKE_DIRECTION_DOWN) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_UP);
                            }
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (snake_direction_last != SNAKE_DIRECTION_UP &&
                            snake_direction_last != SNAKE_DIRECTION_DOWN) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_DOWN);
                            }
                        }
                        break;
                    case sf::Keyboard::Right:
                        if (snake_direction_last != SNAKE_DIRECTION_RIGHT &&
                            snake_direction_last != SNAKE_DIRECTION_LEFT) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_RIGHT);
                            }
                        }
                        break;
                    case sf::Keyboard::Left:
                        if (snake_direction_last != SNAKE_DIRECTION_LEFT &&
                            snake_direction_last != SNAKE_DIRECTION_RIGHT) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_LEFT);
                            }
                        }
                        break;
                }

            }
        }
    }
    else{
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                int snake_direction_last = snake_direction_queue.empty() ? game_state.snake_direction: snake_direction_queue.at(0);
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        if (snake_direction_last != SNAKE_DIRECTION_UP && snake_direction_last != SNAKE_DIRECTION_DOWN) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_DOWN);
                            }
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (snake_direction_last != SNAKE_DIRECTION_UP && snake_direction_last != SNAKE_DIRECTION_DOWN) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_UP);
                            }
                        }
                        break;
                    case sf::Keyboard::Right:
                        if (snake_direction_last != SNAKE_DIRECTION_RIGHT && snake_direction_last != SNAKE_DIRECTION_LEFT) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_LEFT);
                            }
                        }
                        break;
                    case sf::Keyboard::Left:
                        if (snake_direction_last != SNAKE_DIRECTION_LEFT && snake_direction_last != SNAKE_DIRECTION_RIGHT) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_RIGHT);
                            }
                        }
                        break;
                }

            }
        }
    }
}

void update_buffer() {
    if(!snake_direction_queue.empty()){
        game_state.snake_direction=snake_direction_queue.back();
        snake_direction_queue.pop_back();
    }
}

void random_event(){
    srand(time(nullptr));
    int random_trap;
    random_trap=rand()%4;
    switch (random_trap) {
        case 0:
            invert_control= true;
            break;
        case 1:
            if (game_state.speed>30){
                game_state.speed=40;
            } else{
                switch (game_state.speed) {
                    case 30:
                        game_state.speed=20;
                        break;
                    case 15:
                        game_state.speed=10;
                        break;
                    case 10:
                        game_state.speed=5;
                        break;

                }
            }
            break;
        case 2:
            if (game_state.score >= 10){
                game_state.score -= 10;
            } else{
                game_state.score=0;
            }
            score_decrease= true;
            break;
        case 3:
            game_state.snake_length +=5;
            length_increase= true;
            break;
    }
}

void normal_game(){
    event_green = false;
    game_state.speed = game_state.speed_last;

    if(length_increase){
        length_increase = false;
        game_state.snake_length -= 5;
    }

    if(score_decrease) {
        game_state.score = game_state.last_score;
        score_decrease = false;
    }

    invert_control = false;

    x = r; y = g; z = b;
}

int random_bonus(){
    srand(time(nullptr));
    int bonus=rand()%5;
    switch ((bonus)) {
        case 0:
            game_state.score += 15;
            break;
        case 1:
            return 1;
        case 2:
            game_state.speed = 130;
            break;
        case 3:
            if (game_state.snake_length > 9) {
                game_state.snake_length -= 5;
            }
            break;
        case 4:
            game_state.count_of_lifes +=5;
            x=0; y=220; z=255;
            event_yellow=true;
            lifes_color=5;
            break;


    }
}

void update_window(sf::RenderWindow&window){
    if (lifes_color==0&&event_green){
        x=50; y=185; z=50;
    }
    window.clear(sf::Color(x,y,z));
    sf::sleep(sf::milliseconds(game_state.speed));
}

void make_move() {
    game_last_states.push_back(game_state);
    if (game_last_states.size() > 10) {
        game_last_states.erase(game_last_states.begin());
    }

    switch (game_state.snake_direction) {
        case SNAKE_DIRECTION_RIGHT:
            game_state.snake_position_x++;
            if (game_state.snake_position_x > field_size_x - 1){
                game_state.snake_position_x = 0;
            }
            break;
        case SNAKE_DIRECTION_LEFT:
            game_state.snake_position_x--;
            if (game_state.snake_position_x < 0){
                game_state.snake_position_x = field_size_x - 1;
            }
            break;
        case SNAKE_DIRECTION_DOWN:
            game_state.snake_position_y++;
            if (game_state.snake_position_y > field_size_y - 1){
                game_state.snake_position_y = 0;
            }
            break;
        case SNAKE_DIRECTION_UP:
            game_state.snake_position_y--;
            if (game_state.snake_position_y < 0){
                game_state.snake_position_y = field_size_y - 1;
            }
            break;
    }

    if(game_state.field[game_state.snake_position_y][game_state.snake_position_x]!=FIELD_CELL_TYPE_NONE){
        switch (game_state.field[game_state.snake_position_y][game_state.snake_position_x]) {
            case FIELD_CELL_TYPE_APPLE:
                game_state.last_score = game_state.score;
                game_state.last_score++;
                game_state.score++;
                game_state.snake_length++;
                count_of_apples++;
                if (count_of_apples==10){
                    add_green_apple();
                    count_of_apples=0;
                }
                count_of_red_apples++;
                if (count_of_red_apples==5){
                    add_heart();
                }
                grow_snake();
                add_apple();

                if(game_state.score != 0 && game_state.score % 15 == 0){
                    add_yellow_apple();
                }

                break;
            case FIELD_CELL_TYPE_GREEN_APPLE:
                count_of_red_apples=0;
                count_of_apples=0;
                random_event();
                event_green = true;
                break;
            case FIELD_CELL_TYPE_WALL:
                if (game_state.count_of_lifes !=0) {
                    rall_back=true;
                    if(event_yellow){
                        lifes_color--;
                        switch (lifes_color) {
                            case 4:
                                x = 255;
                                y = 20;
                                z = 147;
                            case 3:
                                x = 255;
                                y = 140;
                                z = 0;
                                break;
                            case 2:
                                x = 109;
                                y = 0;
                                z = 139;
                                break;
                            case 1:
                                x = 255;
                                y = 215;
                                z = 0;
                                break;
                            default:
                                event_yellow = false;
                                if (!event_green) {
                                    x = r;
                                    y = g;
                                    z = b;
                                } else {
                                    x = 50;
                                    y = 185;
                                    z = 50;
                                }
                        }
                    }
                }
                else{
                    game_over=true;
                }
                break;
            case FIELD_CELL_TYPE_HEART:
                normal_game();
                count_of_hearts++;
                if(count_of_hearts == 5){
                    game_state.count_of_lifes++;
                }
                break;
            case FIELD_CELL_TYPE_YELLOW_APPLE:
                if (random_bonus()==1) {
                    for (int m=0; m<2; m++){
                        add_heart;
                    }
                }
                break;
            default:
                if(game_state.field[game_state.snake_position_y][game_state.snake_position_x]){
                    if(game_state.count_of_lifes!=0){
                rall_back=true;
                if(event_yellow){
                    lifes_color--;
                    switch (lifes_color) {
                        case 4:
                            x = 255;
                            y = 20;
                            z = 147;
                        case 3:
                            x = 255;
                            y = 140;
                            z = 0;
                            break;
                        case 2:
                            x = 109;
                            y = 0;
                            z = 139;
                            break;
                        case 1:
                            x = 255;
                            y = 215;
                            z = 0;
                            break;
                        default:
                            event_yellow = false;
                            if (!event_green) {
                                x = r;
                                y = g;
                                z = b;
                            } else {
                                x = 50;
                                y = 185;
                                z = 50;
                            }
                    }
                }
        }
        else{
            game_over=true;
        }

                }
                break;

        }
    }

    if(!rall_back){
        for(int j=0;j<field_size_y;j++){
            for(int i=0;i<field_size_x;i++){
                if(game_state.field[j][i]>FIELD_CELL_TYPE_NONE){
                    game_state.field[j][i]--;
                }
            }
        }
        game_state.field[game_state.snake_position_y][game_state.snake_position_x]=game_state.snake_length;
    }
}

void stop_game(sf::RenderWindow& window) {
    if (game_over){
        sf::sleep(sf::seconds(0.5));
        window.close();
    }
}


