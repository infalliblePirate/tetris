#ifndef TETRIS2_0_GAME_H
#define TETRIS2_0_GAME_H

#include <SFML/Graphics.hpp>
#include "Tetromino.h"
#include "GameBoard.h"

class Game {
public:
    Game();
    void run();
private:
    void handle_input(sf::Event& event);
    void draw();
    void update_score();
    void update_score_display();
    bool is_game_over();
    void display_game_over_message();
    void reset_game();
    static void texture_init();
private:
    static sf::Texture texture;
    sf::Sprite sprite;
    sf::RenderWindow window;
    sf::Font font;
    sf::Text score_text;
    Tetromino current_tetromino;
    GameBoard board;
    sf::Clock clock;
    float timer{};
    float time{};
    float delay = 0.5;
    int score = 0;
};


#endif //TETRIS2_0_GAME_H
