#include "card.hpp"

#include <format>
#include <utility>

namespace cards
{
    auto get_rank_value(const rank& r) -> unsigned int
    {
        switch (r)
        {
            case rank::TWO:
            case rank::THREE:
            case rank::FOUR:
            case rank::FIVE:
            case rank::SIX:
            case rank::SEVEN:
            case rank::EIGHT:
            case rank::NINE:
                return std::to_underlying(r);

            case rank::JACK:
            case rank::QUEEN:
            case rank::KING:
                return 10;

            case rank::ACE:
                return 1; //we will handle cases where this needs to be 11 in the blackjack code

            default:
                return 0;
        }
    }

    auto get_rank_str(const rank& r) -> std::string
    {
        switch (r)
        {
            case rank::ACE:
                return "Ace";
            case rank::TWO:
                return "2";
            case rank::THREE:
                return "3";
            case rank::FOUR:
                return "4";
            case rank::FIVE:
                return "5";
            case rank::SIX:
                return "6";
            case rank::SEVEN:
                return "7";
            case rank::EIGHT:
                return "8";
            case rank::NINE:
                return "9";
            case rank::TEN:
                return "10";
            case rank::JACK:
                return "Jack";
            case rank::QUEEN:
                return "Queen";
            case rank::KING:
                return "King";
            default:
                return "No rank";
        }
    }

    auto get_short_rank_str(const rank& r) -> std::string
    {
        switch (r)
        {
            case rank::ACE:
                return "A";
            case rank::TWO:
            case rank::THREE:
            case rank::FOUR:
            case rank::FIVE:
            case rank::SIX:
            case rank::SEVEN:
            case rank::EIGHT:
            case rank::NINE:
            case rank::TEN:
                return get_rank_str(r);
            case rank::JACK:
                return "J";
            case rank::QUEEN:
                return "Q";
            case rank::KING:
                return "K";
            default:
                return "No rank"; // keeping this one long to alert us to a problem
        }
    }

    auto get_suit_str(const suit& s) -> std::string
    {
        switch (s)
        {
            case suit::HEART:
                return "Hearts";
            case suit::CLUB:
                return "Clubs";
            case suit::SPADE:
                return "Spades";
            case suit::DIAMOND:
                return "Diamonds";

            default:
                return std::format("Unknown suit of value {}", std::to_underlying(s));
        }
    }

    auto get_suit_symbol(const suit& s) -> std::string
    {
        switch (s)
        {
            case suit::HEART:
                return "♡";
            case suit::CLUB:
                return "♣";
            case suit::SPADE:
                return "♠";
            case suit::DIAMOND:
                return "♢";
            default:
                return "⌨"; // hopefully drawing the Ace of Keyboards alerts us to a problem
        }
    }
} // namespace cards