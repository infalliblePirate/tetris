#ifndef TETRIS2_0_GAMEBOARD_H
#define TETRIS2_0_GAMEBOARD_H

#include "GameProperties.h"
#include "Tetromino.h"

class GameBoard {
public:
    GameBoard() = default;

    bool is_bottom_occupied(const Tetromino& tetromino);
    void update(const Tetromino& tetromino);
    void line_complete();
public:
    int grid[HEIGHT][WIDTH]{};
    int lines_cleared = 0;
};


#endif //TETRIS2_0_GAMEBOARD_H
