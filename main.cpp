#include <algorithm>

#include "blackjack_utils.hpp"
#include "deck.hpp"
#include "player.hpp"
#include "util.hpp"

#include <chrono>
#include <iostream>

int main() {
    // Random generator setup
    const std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());

    auto d = create_deck();
    util::log(std::cout, std::format("Unshuffled Deck:\n{}", util::get_compact_deck_string(d)));

    shuffle_deck(d, generator);
    util::log(std::cout, std::format("\nShuffled deck:\n{}\n", util::get_compact_deck_string(d)));
    // One dealer and one player for now
    std::vector<player> players{};
    players.push_back(player{.is_dealer = true, .hand{}});
    players.push_back(player{.is_dealer = false, .hand{}});

    blackjack::initial_deal(players, d);
    util::log(std::cout, std::format("After dealing, deck is\n{}\n", util::get_compact_deck_string(d)));
    util::log(std::cout, std::format("Number of players including dealer: {}\n", players.size()));
    util::log(std::cout, "Player hands:\n");
    std::ranges::for_each(players, [](auto& p)
    {
        std::string player_type = p.is_dealer ? "Dealer: " : "Player: ";
        util::log(std::cout, std::format("{}{}\n", player_type, players::get_hand_str(p)));
    });

    return 0;
}
