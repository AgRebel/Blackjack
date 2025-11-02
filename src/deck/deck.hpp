#ifndef BLACKJACK_DECK_HPP
#define BLACKJACK_DECK_HPP

#include "card.hpp"

#include <random>
#include <vector>

constexpr auto DECK_SIZE = 52;

struct deck
{
    std::vector<card> cards;
};

auto create_deck() -> deck;

auto shuffle_deck(deck& d, std::mt19937 g) -> void;

#endif //BLACKJACK_DECK_HPP