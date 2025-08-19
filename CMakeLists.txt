cmake_minimum_required(VERSION 3.10)
project(assembler_simulator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(
    game
    src/main.cpp
    src/loaders/LevelLoader.cpp
    src/loaders/SolutionLoader.cpp
    src/simul/Simulator.cpp
)


target_include_directories(game PRIVATE src)