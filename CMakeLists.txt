cmake_minimum_required(VERSION 3.22)
project(testProject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(testProject main.cpp game_methods.cpp game_methods.h vars.h)

set(SFML_DIR "C:\\greensail\\Snakeproject\\lib\\SFML-2.5.1\\lib\\cmake\\SFML")

target_link_libraries(testProject sfml-graphics sfml-audio)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)
