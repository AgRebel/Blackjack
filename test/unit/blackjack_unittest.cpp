#include "blackjack_utils.hpp"
#include "card.hpp"
#include "deck.hpp"
#include "player.hpp"
#include "util.hpp"

#include <catch2/catch_all.hpp>

#include <iostream>

TEST_CASE("Dealing with 2 players")
{
    auto num_players = 2;
    std::vector<player> players{
        player{.is_dealer = true, .hand = {}},
        player{.is_dealer = false, .hand = {}}
    };

    auto d = create_deck();
    std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
    shuffle_deck(d, generator);
    std::vector<card> top_cards = {};
    for (int i = 0; i < 2 * num_players; ++i)
    {
        top_cards.emplace_back(d.cards.at(i));
    }
    util::log(std::cout, std::format("Deck:\n{}\n", util::get_compact_deck_string(d)));
    blackjack::initial_deal(players, d);
    util::log(std::cout, "Hands:\n");
    for (const auto p : players)
    {
        util::log(std::cout, std::format("{}\n", players::get_hand_str(p)));
    }

    auto iter = top_cards.begin();
    for (int i = 0; i < num_players; ++i)
    {
        for (auto&[is_dealer, hand] : players)
        {
            REQUIRE(hand.at(i).s == iter->s);
            REQUIRE(hand.at(i).r == iter->r);
            ++iter;
        }
    }
    util::log(std::cout, std::format("Deck:\n{}\n", util::get_compact_deck_string(d)));
}