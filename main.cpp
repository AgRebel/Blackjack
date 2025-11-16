#include "blackjack_game.hpp"
#include "blackjack_game_utils.hpp"
#include "util.hpp"

#include <chrono>
#include <iostream>
#include <unordered_map>

constexpr auto NUM_HANDS = 1000;
constexpr auto LOG_TO_STD_OUT = false; // set to true for more detailed per-game logging

int main() {
    std::ostream* os = LOG_TO_STD_OUT ? &std::cout : nullptr;
    std::vector<blackjack::Winner> winners{};

    // Random generator setup
    const auto start_time = std::chrono::system_clock::now().time_since_epoch();
    std::mt19937 generator(start_time.count());

    for (int i = 0; i < NUM_HANDS; ++i)
    {
        util::log(os, std::format("Game {}\n", i + 1));
        winners.emplace_back(blackjack::blackjack_game(generator, false, os));
    }

    const auto end_time = std::chrono::system_clock::now().time_since_epoch();
    auto time_spent = std::chrono::duration_cast<std::chrono::milliseconds>(end_time-start_time).count();

    std::unordered_map<blackjack::Winner, int> win_counts;
    for (auto winner : winners)
    {
        win_counts[winner]++;
    }

    // I always want to log these to cout
    util::log(&std::cout, std::format("Dealer wins: {}\n", win_counts[blackjack::Winner::DEALER]));
    util::log(&std::cout, std::format("Player wins: {}\n", win_counts[blackjack::Winner::PLAYER]));
    util::log(&std::cout, std::format("Pushes: {}\n", win_counts[blackjack::Winner::PUSH]));
    util::log(&std::cout, std::format("Time taken: {}ms", time_spent));

    return 0;
}
