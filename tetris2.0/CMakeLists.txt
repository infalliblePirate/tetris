cmake_minimum_required(VERSION 3.26)
project(tetris2_0)

set(CMAKE_CXX_STANDARD 17)

add_executable(tetris2_0 main.cpp
        Tetromino.h
        Tetromino.cpp
        GameBoard.h
        GameBoard.cpp
        GameProperties.h
        Game.h
        Game.cpp
)
target_link_libraries(tetris2_0 sfml-graphics sfml-window sfml-system sfml-audio)