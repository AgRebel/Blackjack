#include "card.hpp"
#include "deck.hpp"

#include <iostream>

int main() {
    // Random generator setup
    std::random_device rd;
    std::mt19937 generator(rd());

    auto d = create_deck();
    shuffle_deck(d, generator);
    std::cout << "\n\nShuffled Deck:\n";
    for (const auto [s, r] : d.cards)
    {
        std::cout << cards::get_short_rank_str(r) << cards::get_suit_symbol(s) << " ";
    }

    return 0;
}