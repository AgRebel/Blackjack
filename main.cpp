#include "blackjack_game_functions.hpp"

#include <chrono>

#include "blackjack_game_loop.hpp"

int main() {
    // Random generator setup
    const std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());

    return blackjack_game_loop(generator);;
}
