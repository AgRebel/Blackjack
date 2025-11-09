#include "blackjack_game_loop.hpp"

#include "blackjack_game_functions.hpp"
#include "player.hpp"
#include "util.hpp"

#include <algorithm>
#include <format>
#include <iostream>

#include "blackjack_rules.h"

auto dealer_turn(player& dealer, deck& d) -> void
{
    auto score = blackjack::hand_score(dealer.hand);
    while (score < DEALER_STAND_TOTAL)
    {
        blackjack::hit(dealer, d);
        score = blackjack::hand_score(dealer.hand);
        util::log(std::cout, "Dealer hand:\n");
        util::log(std::cout, std::format("{}\n", players::get_hand_str(dealer)));
    }
}

auto player_turn(player& p, deck& d) -> void
{
    auto score = blackjack::hand_score(p.hand);
    char play = 'a';
    while (score <= MAX_SCORE && play != 's')
    {
        std::cout << "(h)it or (s)tay?\n";
        std::cin >> play;
        if (play == 'h')
        {
            blackjack::hit(p, d);
        }
        else if (play != 's')
        {
            std::cout << "Input must be h for hit or s for stay\n";
            continue;
        }
        score = blackjack::hand_score(p.hand);
        util::log(std::cout, "Player hand:\n");
        util::log(std::cout, std::format("{}\n", players::get_hand_str(p)));
    }
}

auto blackjack_game_loop(std::mt19937 generator) -> int
{
    auto d = create_deck();

    shuffle_deck(d, generator);

    // One dealer and one player for now
    std::vector<player> players{};
    players.push_back(player{.is_dealer = true, .hand{}});
    players.push_back(player{.is_dealer = false, .hand{}});

    blackjack::initial_deal(players, d);
    util::log(std::cout, "Hands:\n");
    std::ranges::for_each(players, [](auto& p)
    {
        std::string player_type = p.is_dealer ? "Dealer: " : "Player: ";
        util::log(std::cout, std::format("{}{}\n", player_type, players::get_hand_str(p)));
    });

    //player's turn(s)
    player_turn(players[1], d);

    // once player is done, dealer's turn
    dealer_turn(players[0], d);

    auto dealer_score = blackjack::hand_score(players[0].hand);
    auto player_score = blackjack::hand_score(players[1].hand);

    util::log(std::cout, std::format("Dealer score: {}\n", dealer_score <= MAX_SCORE ? std::to_string(dealer_score) : "Bust"));
    util::log(std::cout, std::format("Player score: {}\n", player_score <= MAX_SCORE ? std::to_string(player_score) : "Bust"));
    std::string winner = "Player";
    if (player_score > MAX_SCORE or (player_score < dealer_score and dealer_score <= MAX_SCORE))
    {
        winner = "Dealer";
    }
    if (player_score == dealer_score and (player_score <= MAX_SCORE and dealer_score <= MAX_SCORE))
    {
        winner = "Push, all bets refunded";
    }
    util::log(std::cout, std::format("Winner: {}!\n", winner));

    return 0;
}
