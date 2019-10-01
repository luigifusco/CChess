cmake_minimum_required(VERSION 3.14)
project(cchess)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-fopenmp -O3")

add_executable(cchess main.c gui.c move.c gamestate.c minimax.c config.c)

target_link_libraries(cchess SDL2)