#include "deck.hpp"
#include "util.hpp"

#include <catch2/catch_all.hpp>

#include <chrono>
#include <iostream>
#include <ranges>

auto print_two_decks(const deck& d1, const deck&d2) -> void
{
    util::log(&std::cout, std::format("first deck:{}\nsecond deck:\n{}\n\b", get_compact_deck_string(d1), get_compact_deck_string(d2)));
}

TEST_CASE("Deck creation")
{
    std::map<cards::suit, int> num_suits{
    {cards::suit::HEART, 0},
    {cards::suit::CLUB, 0},
    {cards::suit::SPADE, 0},
    {cards::suit::DIAMOND, 0}
    };

    std::map<cards::rank, int> num_ranks{
    {cards::rank::ACE, 0},
    {cards::rank::TWO, 0},
    {cards::rank::THREE, 0},
    {cards::rank::FOUR, 0},
    {cards::rank::FIVE, 0},
    {cards::rank::SIX, 0},
    {cards::rank::SEVEN, 0},
    {cards::rank::EIGHT, 0},
    {cards::rank::NINE, 0},
    {cards::rank::TEN, 0},
    {cards::rank::JACK, 0},
    {cards::rank::QUEEN, 0},
    {cards::rank::KING, 0},
    };

    REQUIRE(num_suits.size() == static_cast<int>(cards::suit::LAST)); // because suit starts at 0
    REQUIRE(num_ranks.size() == static_cast<int>(cards::rank::LAST) - 1); // because rank starts at 1

    auto d = create_deck();
    REQUIRE(d.cards.size() == decks::DECK_SIZE);
    for (auto c : d.cards)
    {
        num_ranks[c.r]++;
        num_suits[c.s]++;
    }

    for (auto s : util::iterate_enum(cards::suit::HEART, cards::suit::LAST))
    {
        REQUIRE(num_suits[s] == static_cast<int>(cards::rank::LAST) - 1);
    }

    for (auto r : util::iterate_enum(cards::rank::ACE, cards::rank::LAST))
    {
        REQUIRE(num_ranks[r] == static_cast<int>(cards::suit::LAST));
    }
}

TEST_CASE("Shuffling")
{
    std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
    auto unshuffled = create_deck();
    auto shuffled = create_deck();

    REQUIRE(unshuffled.cards.size() == decks::DECK_SIZE);
    REQUIRE(shuffled.cards.size() == decks::DECK_SIZE);

    // Require that we have two identical unshuffled decks
    for (auto const& [s, u] : std::views::zip(unshuffled.cards, shuffled.cards))
    {
        REQUIRE(s.r == u.r);
        REQUIRE(s.s == u.s);
    }

    print_two_decks(unshuffled, shuffled);

    shuffle_deck(shuffled, generator);

    auto not_identical = 0;
    for (auto const& [s, u] : std::views::zip(unshuffled.cards, shuffled.cards))
    {
        if (s.r != u.r or s.s != u.s)
        {
            not_identical++;
        }
    }
    print_two_decks(unshuffled, shuffled);
    // This test could fail once every 8.0658 x 10 ^ 67 tries on average.  I will live with it.
    REQUIRE(not_identical > 0);

    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    shuffle_deck(unshuffled, generator);
    not_identical = 0;
    for (auto const& [s, u] : std::views::zip(unshuffled.cards, shuffled.cards))
    {
        if (s.r != u.r or s.s != u.s)
        {
            not_identical++;
        }
    }
    print_two_decks(unshuffled, shuffled);
    // This test could fail once every (8.0658 x 10 ^ 67)^2 tries on average.  I will definitely live with it.
    REQUIRE(not_identical > 0);
}