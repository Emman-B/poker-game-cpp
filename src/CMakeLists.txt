cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(poker_game)

add_executable(
    poker_game
    card.cpp
    deck.cpp
    game_logic.cpp
    main.cpp
)