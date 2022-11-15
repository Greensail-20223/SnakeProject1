#include "vars.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <vector>
#include "game_methods.h"

int main() {
    srand(time(nullptr));
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Anaconda", sf::Style::Close);
    clear_field();
    start_game();
    while (window.isOpen()){
        game_control(window);
        update_buffer();
        make_move();
        update_window(window);
        draw_field(window);
        stop_game(window);
        window.display();
    }

    return 0;
}
