#define CATCH_CONFIG_MAIN

#include "card.hpp"
#include "util.hpp"

#include <catch2/catch_all.hpp>

TEST_CASE("Rank values")
{
    for (auto r : util::iterate_enum(cards::rank::ACE, cards::rank::TEN))
    {
        REQUIRE(cards::get_rank_value(r) == std::to_underlying(r));
    }
    for (auto r : util::iterate_enum(cards::rank::JACK, cards::rank::LAST))
    {
        REQUIRE(cards::get_rank_value(r) == 10);
    }
    REQUIRE(cards::get_rank_value(cards::rank::ACE) == 1);
}

TEST_CASE("Rank strings")
{
    REQUIRE(cards::get_rank_str(cards::rank::ACE) == "Ace");
    REQUIRE(cards::get_rank_str(cards::rank::TWO) == "2");
    REQUIRE(cards::get_rank_str(cards::rank::THREE) == "3");
    REQUIRE(cards::get_rank_str(cards::rank::FOUR) == "4");
    REQUIRE(cards::get_rank_str(cards::rank::FIVE) == "5");
    REQUIRE(cards::get_rank_str(cards::rank::SIX) == "6");
    REQUIRE(cards::get_rank_str(cards::rank::SEVEN) == "7");
    REQUIRE(cards::get_rank_str(cards::rank::EIGHT) == "8");
    REQUIRE(cards::get_rank_str(cards::rank::NINE) == "9");
    REQUIRE(cards::get_rank_str(cards::rank::TEN) == "10");
    REQUIRE(cards::get_rank_str(cards::rank::JACK) == "Jack");
    REQUIRE(cards::get_rank_str(cards::rank::QUEEN) == "Queen");
    REQUIRE(cards::get_rank_str(cards::rank::KING) == "King");
}

TEST_CASE("Rank short strings")
{
    REQUIRE(cards::get_short_rank_str(cards::rank::ACE) == "A");
    REQUIRE(cards::get_short_rank_str(cards::rank::TWO) == "2");
    REQUIRE(cards::get_short_rank_str(cards::rank::THREE) == "3");
    REQUIRE(cards::get_short_rank_str(cards::rank::FOUR) == "4");
    REQUIRE(cards::get_short_rank_str(cards::rank::FIVE) == "5");
    REQUIRE(cards::get_short_rank_str(cards::rank::SIX) == "6");
    REQUIRE(cards::get_short_rank_str(cards::rank::SEVEN) == "7");
    REQUIRE(cards::get_short_rank_str(cards::rank::EIGHT) == "8");
    REQUIRE(cards::get_short_rank_str(cards::rank::NINE) == "9");
    REQUIRE(cards::get_short_rank_str(cards::rank::TEN) == "10");
    REQUIRE(cards::get_short_rank_str(cards::rank::JACK) == "J");
    REQUIRE(cards::get_short_rank_str(cards::rank::QUEEN) == "Q");
    REQUIRE(cards::get_short_rank_str(cards::rank::KING) == "K");
}

TEST_CASE("Suits")
{
    REQUIRE(cards::get_suit_str(cards::suit::HEART) == "Hearts");
    REQUIRE(cards::get_suit_str(cards::suit::DIAMOND) == "Diamonds");
    REQUIRE(cards::get_suit_str(cards::suit::SPADE) == "Spades");
    REQUIRE(cards::get_suit_str(cards::suit::CLUB) == "Clubs");
}

TEST_CASE("Suit symbols")
{
    REQUIRE(cards::get_suit_symbol(cards::suit::HEART) == cards::HEART_SYMBOL);
    REQUIRE(cards::get_suit_symbol(cards::suit::DIAMOND) == cards::DIAMOND_SYMBOL);
    REQUIRE(cards::get_suit_symbol(cards::suit::SPADE) == cards::SPADE_SYMBOL);
    REQUIRE(cards::get_suit_symbol(cards::suit::CLUB) == cards::CLUB_SYMBOL);
}

TEST_CASE("Invalid suit/rank passed")
{
    constexpr card c{.s=cards::suit::LAST, .r=cards::rank::LAST};
    REQUIRE(cards::get_rank_str(c.r) == "No rank");
    REQUIRE(cards::get_suit_str(c.s) == "Unknown suit of value 4");
    REQUIRE(cards::get_short_rank_str(c.r) == "No rank");
    REQUIRE(cards::get_suit_symbol(c.s) == "⌨");
    REQUIRE(cards::get_rank_value(c.r) == 0);
}

