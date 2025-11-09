#include "blackjack_game_functions.hpp"

#include "../util/util.hpp"

#include <algorithm>


namespace blackjack
{
    auto hand_score(const std::vector<card>& hand) -> int
    {
        int result = 0;
        for (auto c : hand)
        {
            result += cards::get_rank_value(c.r);
        }
        return result;
    }

    auto hit(player& p, deck& d) -> void
    {
        p.hand.emplace_back((top_card(d)));
    }

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