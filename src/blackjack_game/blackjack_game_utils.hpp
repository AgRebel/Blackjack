#ifndef BLACKJACK_BLACKJACK_GAME_UTILS_HPP
#define BLACKJACK_BLACKJACK_GAME_UTILS_HPP

#include "card.hpp"
#include "deck.hpp"
#include "player.hpp"

#include <vector>

namespace blackjack
{
    auto hand_score(const std::vector<card>& c) -> int;
    auto has_ace(const std::vector<card>& hand) -> bool;
    auto hit(player& p, deck& d) -> void;
    auto initial_deal(std::vector<player>& players, deck& d) -> void;
    auto top_card(deck& d) -> card;
    [[maybe_unused]] auto print_hands(std::vector<player> players, std::ostream* os) -> void;
    auto has_blackjack(const std::vector<card>& hand) -> bool;
} // namespace blackjack

#endif //BLACKJACK_BLACKJACK_GAME_UTILS_HPP