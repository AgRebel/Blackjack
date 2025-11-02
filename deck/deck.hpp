#ifndef BLACKJACK_DECK_HPP
#define BLACKJACK_DECK_HPP

#include "card.hpp"

#include <vector>

constexpr auto DECK_SIZE = 52;

struct deck
{
    std::vector<card> cards;
};

auto create_deck() -> std::vector<card>;

auto shuffle_deck(deck& d);

#endif //BLACKJACK_DECK_HPP