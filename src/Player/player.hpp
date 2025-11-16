#ifndef BLACKJACK_PLAYER_HPP
#define BLACKJACK_PLAYER_HPP

#include "card.hpp"

#include <vector>

struct player
{
    bool is_dealer = false;
    std::vector<card> hand;
};

namespace players
{
    auto get_hand_str(const std::vector<card>& hand) -> std::string;
} // namespace player

#endif //BLACKJACK_PLAYER_HPP