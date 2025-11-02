#include "card.hpp"
#include "deck.hpp"
#include "util.hpp"

#include <iostream>

int main() {
    auto d = create_deck();
    std::cout << "Deck:\n";
    for (const auto [s, r] : d)
    {
        std::cout << get_rank_str(r) << " of " << cards::get_suit_str(s) << "\n";
    }
    return 0;
}