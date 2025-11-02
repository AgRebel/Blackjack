#include "deck.hpp"

#include "card.hpp"
#include "util.hpp"

auto create_deck() -> std::vector<card>
{
    std::vector<card> d;
    for (const cards::suit s : util::iterate_enum(cards::suit::HEART, cards::suit::LAST))
    {
        for (const cards::rank r : util::iterate_enum(cards::rank::ACE, cards::rank::LAST))
        {
            d.emplace_back(card{.s = s, .r = r});
        }
    }

    return d;
}

auto shuffle_deck(deck& d)
{

}