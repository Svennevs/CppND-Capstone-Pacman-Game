cmake_minimum_required(VERSION 3.7)

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

add_executable(Pacman src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/agent.cpp src/fields.cpp) 
target_link_libraries(Pacman ${SDL2_LIBRARIES})