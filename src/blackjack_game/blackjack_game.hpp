#ifndef BLACKJACK_BLACKJACK_GAME_HPP
#define BLACKJACK_BLACKJACK_GAME_HPP

#include "blackjack_rules.hpp"
#include "player.hpp"
#include "strategies.hpp"

#include <iostream>
#include <random>

namespace blackjack
{
    auto blackjack_game(std::mt19937& generator,
                        std::vector<player>& players,
                        bool manual = true,
                        std::ostream* os = &std::cout,
                        const strategy &s = strategies::simple_strategy) -> Winner;
}

#endif //BLACKJACK_BLACKJACK_GAME_HPP