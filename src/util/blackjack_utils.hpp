#ifndef BLACKJACK_BLACKJACK_UTILS_HPP
#define BLACKJACK_BLACKJACK_UTILS_HPP

#include "card.hpp"
#include "deck.hpp"
#include "player.hpp"

#include <vector>

namespace blackjack
{
    auto initial_deal(std::vector<player>& players, deck& d) -> void;
    auto top_card(deck& d) -> card;
} // namespace blackjack

#endif //BLACKJACK_BLACKJACK_UTILS_HPP