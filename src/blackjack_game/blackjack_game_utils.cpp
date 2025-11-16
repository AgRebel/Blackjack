#include "blackjack_game_utils.hpp"

#include "../util/util.hpp"

#include "blackjack_rules.hpp"

#include <algorithm>

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

    [[maybe_unused]] auto print_hands(std::vector<player> players, std::ostream* os) -> void
    {
        util::log(os, "Hands:\n");
        std::ranges::for_each(players, [os](auto& p)
        {
            std::string player_type = p.is_dealer ? "Dealer: " : "Player: ";
            util::log(os, std::format("{}{}\n", player_type, players::get_hand_str(p.hand)));
        });
    }
} // namespace blackjack