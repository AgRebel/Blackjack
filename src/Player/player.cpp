#include "player.hpp"

#include <format>
#include <string>

namespace players
{
    auto get_hand_str(const std::vector<card>& hand) -> std::string
    {
        std::string hand_str;
        for (const auto [s, r] : hand)
        {
            hand_str.append(std::format("{}{} ", cards::get_short_rank_str(r), cards::get_suit_symbol(s)));
        }
        return hand_str;
    }
} // namespace players