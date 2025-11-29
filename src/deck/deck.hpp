#ifndef BLACKJACK_DECK_HPP
#define BLACKJACK_DECK_HPP

#include "card.hpp"

#include <random>
#include <deque>
#include <variant>

namespace decks
{
    constexpr auto DECK_SIZE = 52;
    constexpr auto VEGAS_SHOE_SIZE = 6;
    // We will reshuffle if shoe has between low_bound and upper_bound cards left, randomly
    // this represents the idea of the "cut card" that vegas puts in a shoe of cards
    constexpr auto VEGAS_RESHUFFLE_LOW_BOUND = DECK_SIZE;
    constexpr auto VEGAS_RESHUFFLE_UPPER_BOUND = DECK_SIZE *2;
} // namespace decks

using deck = std::deque<card>;

struct shoe
{
    deck cards;
    int num_decks;
    int cut_card;
};

auto create_deck() -> deck;

auto create_shoe(int num_decks) -> shoe;

auto get_compact_str(const deck& d) -> std::string;

auto shuffle(deck& cards, std::mt19937& g) -> void;

#endif //BLACKJACK_DECK_HPP