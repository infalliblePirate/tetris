#include "GameBoard.h"

bool GameBoard::is_bottom_occupied(const Tetromino& tetromino) { // checks if the  current coordinates were already occupied by other tetro

  for (int i = 0; i < 4; ++i) {
    int x = tetromino.m_tetro_coord[i].x;
    int y = tetromino.m_tetro_coord[i].y;

    // Check if the block is outside the game board or if it's occupied
    if (y >= 0 && grid[y][x] > 0) {
      return true;
    }
  }
  return false;
}

void GameBoard::update(const Tetromino &tetromino) {
  for (int i = 0; i < 4; ++i) {
    grid[tetromino.m_tetro_prev_coord[i].y][tetromino.m_tetro_prev_coord[i].x]  = tetromino.colorN; // colorNum
  }
}

void GameBoard::line_complete() { // checks if the line is complete, if so deletes it
  lines_cleared = 0;
  int k = HEIGHT - 1;
  for (int i = HEIGHT - 1; i > 0; i--) {
    int count = 0;
    for (int j = 0; j < WIDTH; ++j) {
      if (grid[i][j]) count++;
      grid[k][j] = grid[i][j];
    }
    if (count < WIDTH) {
      k--;
    } else {
      lines_cleared++;
    }
  }
}
