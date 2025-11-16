#ifndef BLACKJACK_BLACKJACK_RULES_HPP
#define BLACKJACK_BLACKJACK_RULES_HPP

#include <format>
#include <string>

namespace blackjack
{
    constexpr auto MAX_SCORE = 21;
    constexpr auto DEALER_HITS_ON_SOFT_17 = true;
    constexpr auto DEALER_STAND_TOTAL = 17;

    enum class Winner
    {
        DEALER = 0,
        PLAYER = 1,
        PUSH = 2,
        DEALER_BLACKJACK = 3,
        PLAYER_BLACKJACK = 4
    };

    inline std::string to_string(const Winner& w)
    {
        switch(w)
        {
            case Winner::DEALER: return "Dealer";
            case Winner::PLAYER: return "Player";
            case Winner::PUSH: return "Push";
            default: return "Unknown result";
        }
    }
} // namespace blackjack

template<>
struct std::formatter<blackjack::Winner> : std::formatter<std::string>
{
    auto format(const blackjack::Winner w, std::format_context& ctx) const
    {
        return std::formatter<std::string>::format(to_string(w), ctx);
    }
};

#endif //BLACKJACK_BLACKJACK_RULES_HPP