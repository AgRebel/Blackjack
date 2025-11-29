#ifndef BLACKJACK_BLACKJACK_HAND_HPP
#define BLACKJACK_BLACKJACK_HAND_HPP

#include "blackjack_rules.hpp"
#include "deck.hpp"
#include "player.hpp"
#include "strategies.hpp"

#include <iostream>
#include <random>

namespace blackjack
{
    auto blackjack_hand(std::mt19937& generator,
                        std::vector<player>& players,
                        deck &cards,
                        bool manual = true,
                        std::ostream* os = &std::cout,
                        const strategy &s = strategies::simple_strategy) -> Winner;
}

#endif //BLACKJACK_BLACKJACK_HAND_HPP