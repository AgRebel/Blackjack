#ifndef BLACKJACK_BLACKJACK_AUTO_PLAYER_HPP
#define BLACKJACK_BLACKJACK_AUTO_PLAYER_HPP

#include <random>

#include "strategies.hpp"

namespace blackjack
{
    auto run_auto_blackjack_hands(std::mt19937& generator,
                                  int num_hands,
                                  bool log_games_to_std_out,
                                  const strategy &strat = strategies::simple_strategy) -> void;
}

#endif //BLACKJACK_BLACKJACK_AUTO_PLAYER_HPP