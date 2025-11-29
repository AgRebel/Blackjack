#include "blackjack_auto_player.hpp"

#include <chrono>

constexpr auto NUM_HANDS = 100'000;
// set to true for more detailed per-game logging
constexpr auto LOG_GAMES_TO_STD_OUT = false;

int main()
{
    // Random generator setup
    const auto start_time = std::chrono::system_clock::now().time_since_epoch();
    std::mt19937 generator(start_time.count());

    blackjack::run_auto_blackjack_hands(generator, NUM_HANDS, LOG_GAMES_TO_STD_OUT, strategies::simple_strategy);

    return 0;
}
