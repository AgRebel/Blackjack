#ifndef BLACKJACK_STRATEGIES_HPP
#define BLACKJACK_STRATEGIES_HPP

#include "card.hpp"

#include <functional>

using strategy = std::function<bool(const std::vector<card>&, const cards::rank&)>;

namespace strategies
{
    // For all strategy functions: return true for hit, false for stay

    // for testing/sanity checking purposes
    auto only_stay(const std::vector<card>& hand, const cards::rank& dealer_card_value) -> bool;
    auto only_hit(const std::vector<card>& hand, const cards::rank& dealer_card_value) -> bool;

    // chart from https://www.reddit.com/r/dankmemer/comments/mllo6s/ultimate_blackjack_strategy_chart/#lightbox
    auto simple_strategy(const std::vector<card>& hand, const cards::rank& dealer_card_value) -> bool;
} // namespace strategy

#endif //BLACKJACK_STRATEGIES_HPP