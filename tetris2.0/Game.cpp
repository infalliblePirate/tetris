#include "Game.h"
#include <iostream>

sf::Texture Game::texture;

Game::Game() {
  window.create(sf::VideoMode(240, 510), "tetris");
  texture_init();
  if (!font.loadFromFile(RESOURCE_PATH + "OpenSans.ttf")) {
    std::cerr << "Error: failed to load font" << std::endl;
  }

  score_text.setFont(font);
  score_text.setCharacterSize(24); // Adjust the text size as needed
  score_text.setFillColor(sf::Color::Black);
  score_text.setPosition(10, 475); // Adjust the position as needed
}

void Game::run() {
  while (window.isOpen()) {
    window.clear(sf::Color::White); // clear window first thing
    //settings for tetrominos falling with a delay
    time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timer += time;

    sf::Event event{};
    handle_input(event);

    if (timer > delay) {
      current_tetromino.move_down();

      if (!current_tetromino.within_board_boundaries() || board.is_bottom_occupied(current_tetromino)) {
        board.update(current_tetromino);

        // If the previous position is out of bounds, the game is over
        if (is_game_over()) {
          while (true) {
            display_game_over_message();


            if (window.pollEvent(event) && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
              break;
          }
          reset_game();
        }

        current_tetromino.create();
      }
      timer = 0;
    }

    board.line_complete();
    update_score_display();

    delay = 0.5;
    draw();
    window.display();
  }
}

void Game::handle_input(sf::Event &event) {
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window.close();

    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Up)
        current_tetromino.rotate();
      else if (event.key.code == sf::Keyboard::Left)
        current_tetromino.move_left();
      else if (event.key.code == sf::Keyboard::Right)
        current_tetromino.move_right();
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        reset_game();
      }

      if (board.is_bottom_occupied(current_tetromino)) {
        current_tetromino.set_prev_coord();
      }
    }
  }
  if (event.key.code == sf::Keyboard::Down)
    delay = 0.05;
}

bool Game::is_game_over() {
  bool is_bottom_occupied = board.is_bottom_occupied(current_tetromino);
  for (int i = 0; i < 4; ++i) {
    if (is_bottom_occupied && current_tetromino.m_tetro_prev_coord[i].y == 0) { // used after tetro moving down, so we need to get prev_coord
      return true;
    }
  }
  return false;
}

void Game::display_game_over_message() {
  window.clear(sf::Color::White); // clear all the unnecessary stuff
  sf::Font font;
  if (!font.loadFromFile(RESOURCE_PATH + "OpenSans.ttf")) {
    std::cerr << "Error: Failed to load texture." << std::endl;
  }

  sf::Text game_over_text("Game Over, 'r' to restart\nScore: " + std::to_string(score), font, 20);
  game_over_text.setPosition(0, 215);
  game_over_text.setColor(sf::Color::Red);

  window.draw(game_over_text);
  window.display();
}

void Game::reset_game() {
  window.clear(sf::Color::White);
  // Clear the game board
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      board.grid[i][j] = 0;
    }
  }

  score = 0;
  current_tetromino.create();
  timer = 0;
  run();
}

void Game::draw() {
  // draw sprites falling
  for (int i = 0; i < 4; ++i) {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(current_tetromino.colorN * BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE));
    sprite.setPosition((float)current_tetromino.m_tetro_coord[i].x * BLOCK_SIZE, (float)current_tetromino.m_tetro_coord[i].y * BLOCK_SIZE);
    window.draw(sprite);
  }

  // draw sprites lying
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      if (board.grid[i][j] == 0) continue;
      sprite.setTexture(texture);
      sprite.setTextureRect(sf::IntRect(board.grid[i][j] * BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE));
      sprite.setPosition((float)j * BLOCK_SIZE, (float)i * BLOCK_SIZE);
      window.draw(sprite);
    }
  }

  // draw text
  window.draw(score_text);
}

void Game::update_score_display() {
  update_score();
  // convert the score to a string
  std::string scoreStr = "Score: " + std::to_string(score);

  // update the text
  score_text.setString(scoreStr);
}

void Game::texture_init() {
  if (!texture.loadFromFile(RESOURCE_PATH + "blockPalette.png")) {
    std::cerr << "Error: Failed to load texture." << std::endl;
  }
}

void Game::update_score() {
  switch (board.lines_cleared) {
    case 1:
      score += 100;
      break;
    case 2:
      score += 300;
      break;
    case 3:
      score += 500;
      break;
    case 4:
      score += 800;
      break;
    default:
      break;
  }
}
