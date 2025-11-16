#include "blackjack_game.hpp"
#include "blackjack_game_utils.hpp"
#include "blackjack_rules.hpp"
#include "card.hpp"
#include "deck.hpp"
#include "player.hpp"
#include "util.hpp"

#include <catch2/catch_all.hpp>

#include <iostream>

auto setup_table(int num_players) -> std::pair<std::vector<player>, deck>
{
    std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::vector players{
        player{.is_dealer = true, .hand = {}}
    };

    for (int i = 1; i < num_players; ++i)
    {
        players.emplace_back(player{.is_dealer = false, .hand = {}});
    }

    auto d = create_deck();
    shuffle_deck(d, generator);

    return {players, d};
}

TEST_CASE("Dealing with 2 players")
{
    constexpr auto num_players = 2;
    auto [players, d] = setup_table(num_players);

    std::vector<card> top_cards = {};
    for (int i = 0; i < 2 * num_players; ++i)
    {
        top_cards.emplace_back(d.cards.at(i));
    }
    util::log(&std::cout, std::format("Deck:\n{}\n", get_compact_deck_string(d)));

    blackjack::initial_deal(players, d);

    util::log(&std::cout, "Hands:\n");
    for (const auto p : players)
    {
        util::log(&std::cout, std::format("{}\n", players::get_hand_str(p.hand)));
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
    util::log(&std::cout, std::format("Deck:\n{}\n", get_compact_deck_string(d)));
}

TEST_CASE("Hitting")
{
    constexpr auto num_players = 2;
    auto [players, d] = setup_table(num_players);

    blackjack::initial_deal(players, d);
    REQUIRE(players[1].hand.size() == 2);

    //Hit a few times
    blackjack::hit(players[1], d);
    REQUIRE(players[1].hand.size() == 3);
    blackjack::hit(players[1], d);
    REQUIRE(players[1].hand.size() == 4);
}

TEST_CASE("Scoring")
{
    player p{.is_dealer = true,
        .hand = {card{.s = cards::suit::SPADE, .r = cards::rank::ACE},
                {card{.s = cards::suit::CLUB, .r = cards::rank::EIGHT}}}
        };

    REQUIRE(p.hand.size() == 2);
    // Ace + 8
    REQUIRE(blackjack::hand_score(p.hand) == 19);
    p.hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::ACE});
    // Ace + 8 + Ace
    REQUIRE(blackjack::hand_score(p.hand) == 20);
    // Ace + 8 + Ace + 7
    p.hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::SEVEN});
    REQUIRE(blackjack::hand_score(p.hand) == 17);

    p.hand.clear();
    p.hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::ACE});
    p.hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::TWO});
    // Ace + 2
    REQUIRE(blackjack::hand_score(p.hand) == 13);
}

TEST_CASE("Automated games")
{
    std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
    auto num_games = 100000;

    std::vector<blackjack::Winner> winners{};

    for (int i = 0; i < num_games; ++i)
    {
        winners.emplace_back(blackjack::blackjack_game(generator, false, nullptr));
    }

    std::unordered_map<blackjack::Winner, int> win_counts;
    for (auto winner : winners)
    {
        win_counts[winner]++;
    }

    const auto dealer_wins = win_counts[blackjack::Winner::DEALER];
    const auto player_wins = win_counts[blackjack::Winner::PLAYER];
    const auto pushes = win_counts[blackjack::Winner::PUSH];

    util::log(&std::cout, std::format("Number of games run: {}\n", num_games));
    util::log(&std::cout, std::format("Dealer wins: {}\n", win_counts[blackjack::Winner::DEALER]));
    util::log(&std::cout, std::format("Player wins: {}\n", win_counts[blackjack::Winner::PLAYER]));
    util::log(&std::cout, std::format("Pushes: {}\n", win_counts[blackjack::Winner::PUSH]));

    REQUIRE(dealer_wins + player_wins + pushes == num_games);
}
