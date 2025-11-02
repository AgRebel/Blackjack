cmake_minimum_required(VERSION 4.0)
project(blackjack)

set(CMAKE_CXX_STANDARD 23)

add_executable(blackjack main.cpp
        card/card.hpp
        card/card.cpp
        util/util.hpp
        deck/deck.hpp)

target_include_directories(blackjack PUBLIC ./card ./util)