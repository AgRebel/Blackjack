cmake_minimum_required(VERSION 4.0)
project(blackjack)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_DIR "src")
set(TEST_DIR "test")
set(INCLUDE_DIRS
        "${SOURCE_DIR}/card"
        "${SOURCE_DIR}/deck"
        "${SOURCE_DIR}/util"
        "${SOURCE_DIR}/player"
        "${SOURCE_DIR}/blackjack_game"
        "${TEST_DIR}"
)

add_executable(blackjack main.cpp
        ${SOURCE_DIR}/card/card.cpp
        ${SOURCE_DIR}/deck/deck.cpp
        ${SOURCE_DIR}/player/player.cpp
        ${SOURCE_DIR}/util/util.cpp
        ${SOURCE_DIR}/blackjack_game/blackjack_game_functions.cpp
        ${SOURCE_DIR}/blackjack_game/blackjack_rules.h
        ${SOURCE_DIR}/blackjack_game/blackjack_game_loop.hpp
        ${SOURCE_DIR}/blackjack_game/blackjack_game_loop.cpp)
target_include_directories(blackjack PUBLIC ${INCLUDE_DIRS})

find_package(Catch2 3 REQUIRED)

add_executable(tests
        ${SOURCE_DIR}/card/card.cpp
        ${SOURCE_DIR}/deck/deck.cpp
        ${SOURCE_DIR}/player/player.cpp
        ${SOURCE_DIR}/util/util.cpp
        ${SOURCE_DIR}/blackjack_game/blackjack_game_functions.cpp
        ${TEST_DIR}/unit/card_unittest.cpp
        ${TEST_DIR}/unit/deck_unittest.cpp
        ${TEST_DIR}/unit/blackjack_unittest.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(tests PUBLIC ${TEST_DIR}/unit ${INCLUDE_DIRS})
include(CTest)
include(Catch)
catch_discover_tests(tests)