#ifndef BLACKJACK_CARD_HPP
#define BLACKJACK_CARD_HPP

#include <string>

namespace cards
{
    constexpr auto HEART_SYMBOL = "♡";
    constexpr auto CLUB_SYMBOL = "♣";
    constexpr auto SPADE_SYMBOL = "♠";
    constexpr auto DIAMOND_SYMBOL = "♢";

    enum class suit
    {
        HEART = 0,
        CLUB = 1,
        SPADE = 2,
        DIAMOND = 3,
        LAST = 4
    };

    enum class rank
    {
        ACE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9,
        TEN = 10,
        JACK = 11,
        QUEEN = 12,
        KING = 13,
        LAST = 14
    };

    auto get_rank_value(const rank& r) -> unsigned int;
    auto get_rank_str(const rank& r) -> std::string;
    auto get_short_rank_str(const rank& r) -> std::string;

    auto get_suit_str(const suit& s) -> std::string;
    auto get_suit_symbol(const suit& s) -> std::string;
} // namespace cards

struct card
{
    cards::suit s;
    cards::rank r;
};

#endif //BLACKJACK_CARD_HPP