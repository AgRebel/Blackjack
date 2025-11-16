#include <algorithm>

#include "blackjack_game.hpp"
#include "blackjack_game_utils.hpp"
#include "util.hpp"

#include <chrono>
#include <iostream>
#include <unordered_map>

constexpr auto NUM_HANDS = 100'000;
constexpr auto LOG_TO_STD_OUT = false; // set to true for more detailed per-game logging

int main() {
    std::ostream* os = LOG_TO_STD_OUT ? &std::cout : nullptr;
    std::vector<blackjack::Winner> winners{};

    // Random generator setup
    const auto start_time = std::chrono::system_clock::now().time_since_epoch();
    std::mt19937 generator(start_time.count());

    // One dealer and one player for now
    std::vector<player> players{};
    players.push_back(player{.is_dealer = true, .hand{}});
    players.push_back(player{.is_dealer = false, .hand{}, .bankroll = 500.0});

    auto& player1 = players.back();

    util::log(&std::cout, std::format("Beginning bankroll: {}\n", player1.bankroll));
    bool broke = false;
    int game_broke = -1;
    double max_bankroll = player1.bankroll;
    int max_bankroll_game = 1;
    double min_bankroll = max_bankroll;
    int min_bankroll_game = 1;
    for (int i = 0; i < NUM_HANDS; ++i)
    {
        util::log(os, std::format("Game {}\n", i + 1));
        auto& bankroll = player1.bankroll;
        bankroll -= blackjack::MIN_BET;
        auto winner = blackjack::blackjack_game(generator, players, false, os, strategies::simple_strategy);
        winners.emplace_back(winner);
        bankroll += blackjack::distribute_winnings(winner, blackjack::MIN_BET);

        if (not broke and bankroll < blackjack::MIN_BET)
        {
            broke = true;
            game_broke = i;
        }


        if (max_bankroll < bankroll)
        {
            max_bankroll = bankroll;
            max_bankroll_game = i;
        }
        if (min_bankroll > bankroll)
        {
            min_bankroll = bankroll;
            min_bankroll_game = i;
        }
    }

    const auto end_time = std::chrono::system_clock::now().time_since_epoch();
    auto time_spent = std::chrono::duration_cast<std::chrono::milliseconds>(end_time-start_time).count();

    std::unordered_map<blackjack::Winner, int> win_counts;
    for (auto winner : winners)
    {
        win_counts[winner]++;
    }

    auto total_games = std::accumulate(win_counts.begin(), win_counts.end(), 0,
                              [](const int sum, const std::pair<const blackjack::Winner, int>& pair) {
                                  return sum + pair.second;
                              });

    // I always want to log these to cout for now
    util::log(&std::cout, std::format("Hands played: {}\n", total_games)); // sanity check
    util::log(&std::cout, std::format("Went broke at game {}\n", game_broke));
    util::log(&std::cout, std::format("Max bankroll: {} at game {}\n", max_bankroll, max_bankroll_game));
    util::log(&std::cout, std::format("Min bankroll: {} at game {}\n", min_bankroll, min_bankroll_game));
    util::log(&std::cout, std::format("Dealer wins minus blackjack: {}\n", win_counts[blackjack::Winner::DEALER]));
    util::log(&std::cout, std::format("Player wins minus blackjack: {}\n", win_counts[blackjack::Winner::PLAYER]));
    util::log(&std::cout, std::format("Player blackjacks: {}\n", win_counts[blackjack::Winner::PLAYER_BLACKJACK]));
    util::log(&std::cout, std::format("Dealer blackjacks: {}\n", win_counts[blackjack::Winner::DEALER_BLACKJACK]));
    util::log(&std::cout, std::format("Pushes: {}\n", win_counts[blackjack::Winner::PUSH]));
    util::log(&std::cout, std::format("Ending bankroll: {}\n", player1.bankroll));
    util::log(&std::cout, std::format("Time taken: {}ms", time_spent));

    return 0;
}
