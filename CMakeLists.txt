cmake_minimum_required(VERSION 3.23)
project(Dinosaur C)

set(CMAKE_C_STANDARD 23)

link_libraries(SDL2 SDL2_image SDL2_ttf)

add_executable(Dinosaur main.c)
