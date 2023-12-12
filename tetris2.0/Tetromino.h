#ifndef TETRIS2_0_TETROMINO_H
#define TETRIS2_0_TETROMINO_H

#include <array>

struct BlockCoord {
    int x, y;
};

class Tetromino {
public:
    Tetromino();
    void create();
    bool within_board_boundaries();
    void move_left();
    void move_right();
    void move_down();
    void rotate();
    void set_prev_coord();
private:
    void set_tetro_coord();
public:
    std::array<BlockCoord, 4> m_tetro_coord;
    std::array<BlockCoord, 4> m_tetro_prev_coord;
    int colorN;
private:
    std::array<std::array<int, 4>, 7> m_tetrotype
            {
                    1, 3, 5, 7, // I
                    1, 2, 3, 4, // S
                    0, 2, 3, 5, // Z
                    0, 2, 3, 4, // T
                    0, 2, 4, 5, // L
                    1, 3, 4, 5, // J
                    0, 1, 2, 3  // O
            };
    int m_type;
};


#endif //TETRIS2_0_TETROMINO_H
