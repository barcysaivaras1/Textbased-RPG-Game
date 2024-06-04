cmake_minimum_required(VERSION 3.28)
project(RPG_GAME)

set(CMAKE_CXX_STANDARD 17)

add_executable(RPG_GAME main.cpp
        character.cpp
        Combat.cpp
)
