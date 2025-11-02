#include "deck.hpp"

#include <algorithm>


#include "card.hpp"
#include "util.hpp"

#include <format>
#include <iostream>

auto create_deck() -> deck
{
    std::vector<card> d;
    for (const cards::suit s : util::iterate_enum(cards::suit::HEART, cards::suit::LAST))
    {
        for (const cards::rank r : util::iterate_enum(cards::rank::ACE, cards::rank::LAST))
        {
            d.emplace_back(card{.s = s, .r = r});
        }
    }

    if (d.size() != DECK_SIZE)
    {
        std::cout << std::format("Deck size should be {} but it is {}", DECK_SIZE, d.size());
    }
    return deck{.cards = std::move(d)};
}

auto shuffle_deck(deck& d, std::mt19937 g) -> void
{
    std::ranges::shuffle(d.cards, g);
}