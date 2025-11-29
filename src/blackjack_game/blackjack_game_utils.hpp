#ifndef BLACKJACK_BLACKJACK_GAME_UTILS_HPP
#define BLACKJACK_BLACKJACK_GAME_UTILS_HPP

#include "blackjack_rules.hpp"
#include "card.hpp"
#include "deck.hpp"
#include "player.hpp"

#include <vector>

namespace blackjack
{
    auto hand_score(const std::vector<card>& c) -> int;
    auto has_ace(const std::vector<card>& hand) -> bool;
    auto hit(player& p, deck& cards) -> void;
    auto initial_deal(std::vector<player>& players, deck& d) -> void;
    auto top_card(deck& cards) -> card;
    [[maybe_unused]] auto print_hands(std::vector<player> players, std::ostream* os) -> void;
    auto has_blackjack(const std::vector<card>& hand) -> bool;

    auto distribute_winnings(const Winner& w, double bet) -> double;
} // namespace blackjack

#endif //BLACKJACK_BLACKJACK_GAME_UTILS_HPP