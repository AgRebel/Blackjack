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
                break;

            case rank::JACK:
            case rank::QUEEN:
            case rank::KING:
                return 10;
                break;

            case rank::ACE:
                return 1;
                break;

            default:
                return 0;
                break;
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

    auto get_suit_str(const suit& s) -> std::string
    {
        switch (s)
        {
            case suit::HEART:
                return "Hearts";
                break;
            case suit::CLUB:
                return "Clubs";
                break;
            case suit::SPADE:
                return "Spades";
                break;
            case suit::DIAMOND:
                return "Diamonds";
                break;

            default:
                return std::format("Unknown suit of value {}", std::to_underlying(s));
        }
    }
} // namespace cards