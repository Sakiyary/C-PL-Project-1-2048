cmake_minimum_required(VERSION 3.16.3)
project(211850016-Project-1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

add_executable(Sakiyary_2048 "Sakiyary_2048.c")
target_link_libraries(Sakiyary_2048 SDL2main)
target_link_libraries(Sakiyary_2048 SDL2)
target_link_libraries(Sakiyary_2048 SDL2_image)
target_link_libraries(Sakiyary_2048 SDL2_ttf)