#include <catch2/catch_all.hpp>

#include <iostream>

#include "strategies.hpp"
#include "util.hpp"

TEST_CASE("Only stay")
{
    for (const cards::rank r : util::iterate_enum(cards::rank::ACE, cards::rank::LAST))
    {
        REQUIRE(strategies::only_stay(std::vector<card>{}, r) == false);
    }

}

TEST_CASE("Only hit")
{
    for (const cards::rank r : util::iterate_enum(cards::rank::ACE, cards::rank::LAST))
    {
        REQUIRE(strategies::only_hit(std::vector<card>{}, r) == true);
    }
}

TEST_CASE("Simple strategy")
{
    // For this test case we just force the player hand to have certain values and then run it through
    // all possible dealer cards showing

    std::vector<card> hand{};
    SECTION("Always hit")
    {
        SECTION("11 or less")
        {
            hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::SIX});
            hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::THREE});
            for (const cards::rank r : util::iterate_enum(cards::rank::ACE, cards::rank::LAST))
            {
                REQUIRE(strategies::simple_strategy(hand, r) == true);
            }
        }

        SECTION("Soft 17 or less")
        {
            hand.clear();
            hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::ACE});
            hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::TEN});

            for (const cards::rank r : util::iterate_enum(cards::rank::ACE, cards::rank::LAST))
            {
                REQUIRE(strategies::simple_strategy(hand, r) == true);
            }
        }
    }

    SECTION("Always stay")
    {
        SECTION("17 or more")
        {
            hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::EIGHT});
            hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::JACK});
            for (const cards::rank r : util::iterate_enum(cards::rank::ACE, cards::rank::LAST))
            {
                REQUIRE(strategies::simple_strategy(hand, r) == false);
            }
        }

        SECTION("Ace + 8")
        {
            hand.clear();
            hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::ACE});
            hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::EIGHT});
            for (const cards::rank r : util::iterate_enum(cards::rank::ACE, cards::rank::LAST))
            {
                REQUIRE(strategies::simple_strategy(hand, r) == false);
            }
        }

        SECTION("Ace + 9")
        {
            hand.clear();
            hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::ACE});
            hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::NINE});
            for (const cards::rank r : util::iterate_enum(cards::rank::ACE, cards::rank::LAST))
            {
                REQUIRE(strategies::simple_strategy(hand, r) == false);
            }
        }
    }

    SECTION("Exactly 12")
    {
        hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::EIGHT});
        hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::FOUR});

        for (const cards::rank r : util::iterate_enum(cards::rank::ACE, cards::rank::LAST))
        {
            switch (r)
            {
                case cards::rank::TWO:
                case cards::rank::THREE:
                case cards::rank::SEVEN:
                case cards::rank::EIGHT:
                case cards::rank::NINE:
                case cards::rank::TEN:
                case cards::rank::JACK:
                case cards::rank::QUEEN:
                case cards::rank::KING:
                case cards::rank::ACE:
                    REQUIRE(strategies::simple_strategy(hand, r) == true);
                    break;
                default:
                    REQUIRE(strategies::simple_strategy(hand, r) == false);
            }
        }
    }

    SECTION("13-16")
    {
        std::vector<std::vector<card>> hands{};
        hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::EIGHT});
        hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::FIVE});
        hands.emplace_back(hand);

        hand.clear();
        hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::SEVEN});
        hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::SEVEN});
        hands.emplace_back(hand);

        hand.clear();
        hand.emplace_back(card{.s = cards::suit::DIAMOND, .r = cards::rank::SEVEN});
        hand.emplace_back(card{.s = cards::suit::CLUB, .r = cards::rank::EIGHT});
        hands.emplace_back(hand);

        hand.clear();
        hand.emplace_back(card{.s = cards::suit::HEART, .r = cards::rank::SEVEN});
        hand.emplace_back(card{.s = cards::suit::CLUB, .r = cards::rank::NINE});
        hands.emplace_back(hand);
        for (const auto h : hands)
        {
            for (const cards::rank r : util::iterate_enum(cards::rank::ACE, cards::rank::LAST))
            {
                switch (r)
                {
                    case cards::rank::SEVEN:
                    case cards::rank::EIGHT:
                    case cards::rank::NINE:
                    case cards::rank::TEN:
                    case cards::rank::JACK:
                    case cards::rank::QUEEN:
                    case cards::rank::KING:
                    case cards::rank::ACE:
                        REQUIRE(strategies::simple_strategy(h, r) == true);
                        break;
                    default:
                        REQUIRE(strategies::simple_strategy(h, r) == false);
                }
            }
        }
    }

    SECTION("Ace + 7")
    {
        hand.emplace_back(card{.s = cards::suit::HEART, .r = cards::rank::ACE});
        hand.emplace_back(card{.s = cards::suit::SPADE, .r = cards::rank::SEVEN});

        for (const cards::rank r : util::iterate_enum(cards::rank::ACE, cards::rank::LAST))
        {
            switch (r)
            {
                case cards::rank::NINE:
                case cards::rank::TEN:
                case cards::rank::JACK:
                case cards::rank::QUEEN:
                case cards::rank::KING:
                case cards::rank::ACE:
                    REQUIRE(strategies::simple_strategy(hand, r) == true);
                    break;
                default:
                    REQUIRE(strategies::simple_strategy(hand, r) == false);
            }
        }
    }
}