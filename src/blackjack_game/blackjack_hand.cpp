#include "blackjack_hand.hpp"

#include "blackjack_utils.hpp"
#include "blackjack_rules.hpp"
#include "player.hpp"
#include "strategies.hpp"
#include "util.hpp"

#include <algorithm>
#include <format>
#include <functional>
#include <iostream>

namespace
{
    auto dealer_turn(player& dealer, deck& cards) -> void
    {
        using namespace blackjack;
        auto score = hand_score(dealer.hand);
        while (score < DEALER_STAND_TOTAL or (score == DEALER_STAND_TOTAL and has_ace(dealer.hand) and DEALER_HITS_ON_SOFT_17))
        {
            hit(dealer, cards);
            score = hand_score(dealer.hand);
        }
    }

    auto manual_player_turn(player& p, deck& cards) -> void
    {
        using namespace blackjack;
        std::ostream* os = &std::cout;
        auto score = hand_score(p.hand);
        char play = 'a';
        while (score <= MAX_SCORE && play != 's')
        {
            util::log(os, std::format("{}{}\n", "Player: ", players::get_hand_str(p.hand)));
            std::cout << "(h)it or (s)tay?\n";
            std::cin >> play;
            if (play == 'h')
            {
                hit(p, cards);
            }
            else if (play != 's')
            {
                std::cout << "Input must be h for hit or s for stay\n";
                continue;
            }
            score = hand_score(p.hand);
            util::log(os, "Player hand:\n");
            util::log(os, std::format("{}\n", players::get_hand_str(p.hand)));
        }
    }

    auto automated_player_turn(player& p, deck& cards, const card& dealer_card, const strategy &strat) -> void
    {
        using namespace blackjack;
        auto hit_or_stay = strat(p.hand, dealer_card.r);
        while (hit_or_stay and hand_score(p.hand) < MAX_SCORE)
        {
            hit(p, cards);
            hit_or_stay = strat(p.hand, dealer_card.r);
        }
    }
} // namespace

namespace blackjack
{
    auto blackjack_hand(std::mt19937& generator,
                        std::vector<player>& players,
                        deck& cards,
                        const bool manual,
                        std::ostream* os,
                        const strategy &s) -> Winner
    {
        auto& dealer = players.front();
        auto& player1 = players.at(1);

        // Ensure empty hands
        dealer.hand.clear();
        player1.hand.clear();

        initial_deal(players, cards);
        if (has_blackjack(dealer.hand))
        {
            return Winner::DEALER_BLACKJACK;
        }
        if (has_blackjack(player1.hand))
        {
            return Winner::PLAYER_BLACKJACK;
        }

        // player(s)' turn(s); could be manual or automated
        manual ? manual_player_turn(player1, cards) :
                 automated_player_turn(player1, cards, dealer.hand.at(0), s);

        // dealer turn; dealer always automated according to rules
        dealer_turn(dealer, cards);

        const auto dealer_score = hand_score(dealer.hand);
        const auto player_score = hand_score(player1.hand);

        util::log(os, std::format("Dealer score: {}\n", dealer_score <= MAX_SCORE ? std::to_string(dealer_score) : "Bust"));
        util::log(os, std::format("Player score: {}\n\n", player_score <= MAX_SCORE ? std::to_string(player_score) : "Bust"));
        if (player_score > MAX_SCORE or (player_score < dealer_score and dealer_score <= MAX_SCORE))
        {
            return Winner::DEALER;
        }
        if (player_score == dealer_score and dealer_score <= MAX_SCORE)
        {
            return Winner::PUSH;
        }
        return Winner::PLAYER;
    }
} // namespace blackjack
