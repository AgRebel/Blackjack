#ifndef BLACKJACK_BLACKJACK_GAME_HPP
#define BLACKJACK_BLACKJACK_GAME_HPP

#include "blackjack_rules.hpp"

#include <iostream>
#include <random>

namespace blackjack
{
    auto blackjack_game(std::mt19937& generator, bool manual = true, std::ostream* os = &std::cout) -> Winner;
}

#endif //BLACKJACK_BLACKJACK_GAME_HPP