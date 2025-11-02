#include "card.hpp"
#include "deck.hpp"

#include <chrono>
#include <iostream>

#include "util.hpp"

int main() {
    // Random generator setup
    const std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());

    auto d = create_deck();
    util::log(std::cout, std::format("Unshuffled Deck:\n{}", util::get_compact_deck_string(d)));

    util::log(std::cout, "\n\nShuffled Decks (5 shuffles):\n");
    for (auto i = 0; i < 5; i++)
    {
        shuffle_deck(d, generator);
        util::log(std::cout, std::format("{}\n", util::get_compact_deck_string(d)));
    }
    return 0;
}
