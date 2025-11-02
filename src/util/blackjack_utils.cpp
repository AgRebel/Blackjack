#include "blackjack_utils.hpp"

#include "util.hpp"


namespace blackjack
{
    auto initial_deal(std::vector<player>& players, deck& d) -> void
    {
        for (int i = 0; i < 2; ++i)
        {
            for (auto&[is_dealer, hand] : players)
            {
                hand.emplace_back(top_card(d));
            }
        }
    }

    auto top_card(deck& d) -> card
    {
        const auto c = d.cards.front();
        d.cards.pop_front();
        return c;
    }
} // namespace blackjack