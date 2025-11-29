#include "blackjack_utils.hpp"

#include "util.hpp"

#include "blackjack_rules.hpp"

#include <algorithm>
#include <iostream>

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
        if (has_ace and result + 10 <= MAX_SCORE)
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

    auto hit(player& p, deck& cards) -> void
    {
        p.hand.emplace_back((top_card(cards)));
    }

    auto initial_deal(std::vector<player>& players, deck& d) -> void
    {
        for (int i = 0; i < 2; ++i)
        {
            for (auto& p : players)
            {
                p.hand.emplace_back(top_card(d));
            }
        }
    }

    auto top_card(deck& cards) -> card
    {
        const auto c = cards.front();
        cards.pop_front();
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

    auto has_blackjack(const std::vector<card>& hand) -> bool
    {
        return hand.size() == 2 and has_ace(hand) and hand_score(hand) == MAX_SCORE;
    }

    auto distribute_winnings(const Winner& w, const double bet) -> double
    {
        switch(w)
        {
            case Winner::DEALER_BLACKJACK:
            case Winner::DEALER:
                return 0.0;
            case Winner::PLAYER:
                return bet * 2.0;
            case Winner::PLAYER_BLACKJACK:
                return bet + bet * BLACKJACK_PAYOUT;
            case Winner::PUSH:
            case Winner::BLACKJACK_PUSH:
                return bet;
            default:
                util::log(&std::cout, std::format("Got an unknown win condition {}\n", std::to_underlying(w)));
                return bet;
        }
    }
} // namespace blackjack