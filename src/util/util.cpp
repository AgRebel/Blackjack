#include "util.hpp"

#include <iostream>

namespace util
{
    auto get_compact_deck_string(const deck &d) -> std::string
    {
        std::string deck_string;
        for (const auto [s, r] : d.cards)
        {
            deck_string.append(cards::get_short_rank_str(r) + cards::get_suit_symbol(s) + " ");
        }
        return deck_string;
    }

    auto log(std::ostream& os, std::string_view s) -> void
    {
        os << s;
    }
}// namespace util