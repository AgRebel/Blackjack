#include "deck.hpp"

#include <algorithm>


#include "card.hpp"
#include "util.hpp"

auto create_deck() -> deck
{
    deck d;
    for (const cards::suit s : util::iterate_enum(cards::suit::HEART, cards::suit::LAST))
    {
        for (const cards::rank r : util::iterate_enum(cards::rank::ACE, cards::rank::LAST))
        {
            d.emplace_back(card{.s = s, .r = r});
        }
    }

    return d;
}

auto create_shoe(const int num_decks) -> shoe
{
    deck d;
    for (int i = 0; i < num_decks; ++i)
    {
        auto cards = create_deck();
        d.insert(d.end(), cards.begin(), cards.end());
    }
    return shoe{.cards = std::move(d), .num_decks = num_decks, .cut_card = decks::VEGAS_RESHUFFLE_LOW_BOUND};
}

auto get_compact_str(const deck &d) -> std::string
{
    std::string result;
    for (const auto [s, r] : d)
    {
        result.append(cards::get_short_rank_str(r) + cards::get_suit_symbol(s) + " ");
    }
    return result;
}

auto shuffle(deck& cards, std::mt19937& g) -> void
{
    std::ranges::shuffle(cards, g);
}

