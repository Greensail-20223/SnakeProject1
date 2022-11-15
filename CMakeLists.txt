cmake_minimum_required(VERSION 3.22)
project(SnakeProject)
set(CMAKE_CXX_STANDARD  23)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(SnakeProject main.cpp game_methods.cpp game_methods.h vars.h)
target_link_libraries(SnakeProject sfml-graphics sfml-audio)

