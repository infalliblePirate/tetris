#include "Tetromino.h"
#include "GameProperties.h"
#include <cstdlib>


Tetromino::Tetromino() {
  create();
}

void Tetromino::create() {
  m_type = rand() % 7;
  colorN = 1 + rand() % 6; // set random color from my palette, start from 1 because 0 represents empty cell
  set_tetro_coord();
}

bool Tetromino::within_board_boundaries() {
  for (int i = 0; i < 4; ++i) {
    if (m_tetro_coord[i].x < 0 || m_tetro_coord[i].x >= WIDTH
        || m_tetro_coord[i].y >= HEIGHT) return false;
  }
  return true;

}

void Tetromino::move_left() {
  for (int i = 0; i < 4; ++i) {
    m_tetro_prev_coord[i] = m_tetro_coord[i];
    m_tetro_coord[i].x--;
  }
  if (!within_board_boundaries()) {
    set_prev_coord();
  }
}

void Tetromino::move_right() {
  for (int i = 0; i < 4; ++i) {
    m_tetro_prev_coord[i] = m_tetro_coord[i];
    m_tetro_coord[i].x++;
  }
  if (!within_board_boundaries()) {
    set_prev_coord();
  }
}

void Tetromino::move_down() {
  for (int i = 0; i < 4; ++i) {
    m_tetro_prev_coord[i] = m_tetro_coord[i];
    m_tetro_coord[i].y++;
  }
}

void Tetromino::rotate() {
  BlockCoord rotationCenter = m_tetro_coord[2];
  std::array<BlockCoord, 4> temp_coord = m_tetro_coord;
  for (int i = 0; i < 4; ++i) {
    int x = m_tetro_coord[i].y - rotationCenter.y;
    int y = m_tetro_coord[i].x - rotationCenter.x;
    temp_coord[i].x = rotationCenter.x - x;
    temp_coord[i].y = rotationCenter.y + y;
  }
  for (int i = 0; i < 4; ++i) { // in case it goes out of boundaries
    if (temp_coord[i].x < 0 || temp_coord[i].x >= WIDTH || temp_coord[i].y >= HEIGHT)
      return;
  }

  m_tetro_coord = temp_coord;
}

void Tetromino::set_tetro_coord() {
  for (int i = 0; i < m_tetrotype[0].size(); ++i) {
    m_tetro_coord[i].x = m_tetrotype[m_type][i] % 2;
    m_tetro_coord[i].y = m_tetrotype[m_type][i] / 2;
  }
}
void Tetromino::set_prev_coord() { // if the tetromino occupies foreign territory, set prev coords
  for (int i = 0; i < 4; ++i) {
    m_tetro_coord[i] = m_tetro_prev_coord[i];
  }
}