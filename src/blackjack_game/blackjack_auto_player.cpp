#include "blackjack_auto_player.hpp"

#include "blackjack_hand.hpp"
#include "blackjack_utils.hpp"
#include "util.hpp"

#include <chrono>
#include <iostream>


namespace blackjack
{
    auto run_auto_blackjack_hands(std::mt19937& generator,
                                  const int num_hands,
                                  const bool log_games_to_std_out,
                                  const strategy& strat) -> void
    {
        const auto start_time = std::chrono::system_clock::now().time_since_epoch();
        std::ostream* os = log_games_to_std_out ? &std::cout : nullptr;
        std::uniform_int_distribution dist(decks::VEGAS_RESHUFFLE_LOW_BOUND, decks::VEGAS_RESHUFFLE_UPPER_BOUND);

        // One dealer and one player for now
        std::vector<player> players{};
        std::vector<Winner> winners{};
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
        auto shoe = create_shoe(decks::VEGAS_SHOE_SIZE);
        shuffle(shoe.cards, generator);

        shoe.cut_card = dist(generator);

        for (int i = 0; i < num_hands; ++i)
        {
            util::log(os, std::format("Game {}\n", i + 1));
            auto& bankroll = player1.bankroll;
            bankroll -= MIN_BET;
            auto winner = blackjack_hand(generator, players, shoe.cards, false, os, strat);
            winners.emplace_back(winner);
            bankroll += distribute_winnings(winner, MIN_BET);

            if (shoe.cards.size() <= shoe.cut_card)
            {
                shoe = create_shoe(decks::VEGAS_SHOE_SIZE);
                shuffle(shoe.cards, generator);
                shoe.cut_card = dist(generator);
            }

            if (not broke and bankroll < MIN_BET)
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

        std::unordered_map<Winner, int> win_counts;
        for (auto winner : winners)
        {
            win_counts[winner]++;
        }

        auto total_games = std::accumulate(win_counts.begin(), win_counts.end(), 0,
                                  [](const int sum, const std::pair<const Winner, int>& pair) {
                                      return sum + pair.second;
                                  });

        // Always logging to cout on this stuff
        util::log(&std::cout, std::format("Hands played: {}\n", total_games)); // sanity check
        util::log(&std::cout, std::format("Went broke at game {}\n", game_broke));
        util::log(&std::cout, std::format("Max bankroll: {} at game {}\n", max_bankroll, max_bankroll_game));
        util::log(&std::cout, std::format("Min bankroll: {} at game {}\n", min_bankroll, min_bankroll_game));
        util::log(&std::cout, std::format("Dealer wins minus blackjack: {}\n", win_counts[Winner::DEALER]));
        util::log(&std::cout, std::format("Player wins minus blackjack: {}\n", win_counts[Winner::PLAYER]));
        util::log(&std::cout, std::format("Player blackjacks (including pushes): {}\n", win_counts[Winner::PLAYER_BLACKJACK] + win_counts[Winner::BLACKJACK_PUSH]));
        util::log(&std::cout, std::format("Dealer blackjacks (including pushes): {}\n", win_counts[Winner::DEALER_BLACKJACK] + win_counts[Winner::BLACKJACK_PUSH]));
        util::log(&std::cout, std::format("Pushes: {}\n", win_counts[Winner::PUSH]));
        util::log(&std::cout, std::format("Blackjack Pushes: {}\n", win_counts[Winner::BLACKJACK_PUSH]));
        util::log(&std::cout, std::format("Ending bankroll: {}\n", player1.bankroll));
        util::log(&std::cout, std::format("Time taken: {}ms", time_spent));
    }
}