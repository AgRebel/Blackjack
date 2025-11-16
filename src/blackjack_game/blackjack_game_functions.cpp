#include "blackjack_game_functions.hpp"

#include "../util/util.hpp"

#include "blackjack_rules.h"


namespace blackjack
{
    auto hand_score(const std::vector<card>& hand) -> int
    {
        int result = 0;
        bool has_ace = false;
        for (auto [s, r] : hand)
        {
            if (r == cards::rank::ACE)
            {
                has_ace = true;
            }
            result += cards::get_rank_value(r);
        }
        // We can only count one ace as 11 because two would make 22 and bust
        // add 10 because we already counted it as 1 before
        if (has_ace and result + 10 < MAX_SCORE)
        {
            result += 10;
        }
        return result;
    }

    auto has_ace(const std::vector<card>& hand) -> bool
    {
        for (auto [s, r] : hand)
        {
            if (r == cards::rank::ACE)
            {
                return true;
            }
        }
        return false;
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