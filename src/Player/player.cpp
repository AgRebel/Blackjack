#include "player.hpp"

#include "util.hpp"

#include <algorithm>
#include <format>
#include <string>

namespace players
{
    auto get_hand_str(const player& p) -> std::string
    {
        std::string hand_str;
        std::ranges::for_each(p.hand, [&](auto& c)
        {
            hand_str.append(std::format("{}{} ", cards::get_short_rank_str(c.r), cards::get_suit_symbol(c.s)));
        });
        return hand_str;
    }
} // namespace players