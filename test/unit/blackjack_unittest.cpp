#include "blackjack_hand.hpp"
#include "blackjack_utils.hpp"
#include "blackjack_rules.hpp"
#include "card.hpp"
#include "deck.hpp"
#include "player.hpp"
#include "util.hpp"

#include <catch2/catch_all.hpp>

#include <iostream>

using namespace blackjack;

auto setup_table(const int num_players) -> std::pair<std::vector<player>, shoe>
{
    std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::vector players{
        player{.is_dealer = true, .hand = {}}
    };

    for (int i = 1; i < num_players; ++i)
    {
        players.emplace_back(player{.is_dealer = false, .hand = {}});
    }

    auto d = create_shoe(1);
    shuffle(d.cards, generator);

    return {players, d};
}

TEST_CASE("Dealing with 2 players")
{
    constexpr auto num_players = 2;
    auto [players, s] = setup_table(num_players);

    std::vector<card> top_cards = {};
    for (int i = 0; i < 2 * num_players; ++i)
    {
        top_cards.emplace_back(s.cards.at(i));
    }
    util::log(&std::cout, std::format("Deck:\n{}\n", get_compact_str(s.cards)));

    blackjack::initial_deal(players, s.cards);

    util::log(&std::cout, "Hands:\n");
    for (const auto& p : players)
    {
        util::log(&std::cout, std::format("{}\n", players::get_hand_str(p.hand)));
    }

    auto iter = top_cards.begin();
    for (int i = 0; i < num_players; ++i)
    {
        for (auto& p : players)
        {
            REQUIRE(p.hand.at(i).s == iter->s);
            REQUIRE(p.hand.at(i).r == iter->r);
            ++iter;
        }
    }
    util::log(&std::cout, std::format("Deck:\n{}\n", get_compact_str(s.cards)));
}

TEST_CASE("Hitting")
{
    constexpr auto num_players = 2;
    auto [players, s] = setup_table(num_players);

    blackjack::initial_deal(players, s.cards);
    REQUIRE(players[1].hand.size() == 2);

    //Hit a few times
    blackjack::hit(players[1], s.cards);
    REQUIRE(players[1].hand.size() == 3);
    blackjack::hit(players[1], s.cards);
    REQUIRE(players[1].hand.size() == 4);
}

TEST_CASE("Scoring")
{
    std::vector<card> hand = {
        card{.s = cards::suit::SPADE, .r = cards::rank::ACE},
       card{.s = cards::suit::CLUB, .r = cards::rank::EIGHT}};


    REQUIRE(hand.size() == 2);
    // Ace + 8
    REQUIRE(hand_score(hand) == 19);
    hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::ACE});
    // Ace + 8 + Ace
    REQUIRE(hand_score(hand) == 20);
    // Ace + 8 + Ace + 7
    hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::SEVEN});
    REQUIRE(hand_score(hand) == 17);

    hand.clear();
    hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::ACE});
    hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::TWO});
    // Ace + 2
    REQUIRE(hand_score(hand) == 13);

    // Blackjack
    hand.clear();
    hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::ACE});
    hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::TEN});
    REQUIRE(hand_score(hand) == MAX_SCORE);
    REQUIRE(has_blackjack(hand));

    hand.pop_back();
    hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::JACK});
    REQUIRE(hand_score(hand) == MAX_SCORE);
    REQUIRE(has_blackjack(hand));

    hand.pop_back();
    hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::QUEEN});
    REQUIRE(hand_score(hand) == MAX_SCORE);
    REQUIRE(has_blackjack(hand));

    hand.pop_back();
    hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::KING});
    REQUIRE(hand_score(hand) == MAX_SCORE);
    REQUIRE(has_blackjack(hand));
}

TEST_CASE("Automated games")
{
    std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
    constexpr auto num_games = 100000;

    std::vector<Winner> winners{};
    std::vector<player> players{};
    players.push_back(player{.is_dealer = true, .hand{}});
    players.push_back(player{.is_dealer = false, .hand{}, .bankroll = 500.0});
    auto d = create_deck();

    for (int i = 0; i < num_games; ++i)
    {
        winners.emplace_back(blackjack_hand(generator, players, d, false, nullptr));
        //Re-shuffle the deck back to full if size < 20 to prevent running out of cards
        if (d.size() < 20)
        {
            d = create_deck();
            shuffle(d, generator);
        }
    }

    std::unordered_map<Winner, int> win_counts;
    for (auto winner : winners)
    {
        win_counts[winner]++;
    }

    REQUIRE(win_counts[Winner::DEALER] +
            win_counts[Winner::PLAYER] +
            win_counts[Winner::PUSH] +
            win_counts[Winner::DEALER_BLACKJACK] +
            win_counts[Winner::PLAYER_BLACKJACK] +
            win_counts[Winner::BLACKJACK_PUSH] == num_games);
}

TEST_CASE("Bet payouts")
{
    for (const Winner w : util::iterate_enum(Winner::DEALER, Winner::LAST))
    {
        constexpr double bet = 10;
        switch(w)
        {
            case Winner::DEALER:
            case Winner::DEALER_BLACKJACK:
                REQUIRE(distribute_winnings(w, bet) == 0.0);
                break;
            case Winner::PLAYER_BLACKJACK:
                REQUIRE(distribute_winnings(w, bet) == bet + bet * BLACKJACK_PAYOUT);
                break;
            case Winner::PLAYER:
                REQUIRE(distribute_winnings(w, bet) == bet * 2.0);
                break;
            case Winner::PUSH:
                REQUIRE(distribute_winnings(w, bet) == bet);
                break;
            default:
                REQUIRE(distribute_winnings(w, bet) == bet);
                break;
        }
    }
}