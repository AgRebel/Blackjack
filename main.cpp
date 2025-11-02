#include "card.hpp"
#include "util.hpp"

#include <iostream>

int main() {
    std::cout << "Suits:\n";
    for (cards::suit s : util::iterate_enum(cards::suit::HEART, cards::suit::LAST))
    {
        std::cout << cards::get_suit_str(s) << " ";
    }

    std::cout << "\n\nRanks:\n";
    for (cards::rank r : util::iterate_enum(cards::rank::ACE, cards::rank::LAST))
    {
        std::cout << cards::get_rank_str(r) << " ";
    }
    return 0;
}606