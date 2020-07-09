set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    poker_game
    card.cpp
    deck.cpp
    game_logic.cpp
    main.cpp
)