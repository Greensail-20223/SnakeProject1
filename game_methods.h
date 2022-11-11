#ifndef TESTPROJECT_GAME_METHODS_H
#define TESTPROJECT_GAME_METHODS_H

#endif //TESTPROJECT_GAME_METHODS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <vector>

void set_sounds();
void set_fonts();
void menu_control(sf::RenderWindow& window_main);
void draw_main_menu(sf::RenderWindow& window_main);
void control_menu_control(sf::RenderWindow &window_main);
void open_control_menu();
void draw_window_color(sf::RenderWindow& window_2);
void open_main_menu();
void help_menu_control(sf::RenderWindow &window_main);
void open_help_menu();
void update_buffer();
void chose_window_color(sf::RenderWindow& window_2);
void set_window_color();
void check_event_2(sf::RenderWindow& window_wall);
void draw_arrow_2(sf::RenderWindow& window_wall);
void draw_wall_choice(sf::RenderWindow& window_wall);
void choose_wall();
void check_event(sf::RenderWindow& window_1);
void draw_arrow(sf::RenderWindow& window_1);
void draw_skin_choice(sf::RenderWindow& window_1);
void choose_skin();
void difficulty_menu_control(sf::RenderWindow &window_main);
void open_difficulty_menu();
void level_menu_control(sf::RenderWindow &window_main);
void open_level_menu();
void set_volume_level();
void volume_menu_control(sf::RenderWindow& window_volume);
void open_volume_menu();
void settings_menu_control(sf::RenderWindow &window_main);
void open_settings_menu();
int get_random_empty_cell();
void add_apple();
void add_heart();
void add_yellow_apple();
void add_green_apple();
void clear_field();
void draw_field(sf::RenderWindow& window);
void grow_snake();
void random_event();
int random_bonus();
void normal_game();
void pause_menu_control(sf::RenderWindow &window_pause, sf::RenderWindow& window);
void open_pause_menu(sf::RenderWindow& window);
void make_move();
void start_game();
void lose_menu_control(sf::RenderWindow &window_main);
void open_lose_menu();
void game_control(sf::RenderWindow& window);
void check_win();
void stop_game(sf::RenderWindow& window);
void update_window(sf::RenderWindow&window);

