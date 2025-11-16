#include "strategies.hpp"

#include "blackjack_game_utils.hpp"
#include "blackjack_rules.hpp"

namespace strategies
{
    using namespace blackjack;
    auto only_stay([[maybe_unused]] const std::vector<card>& hand, [[maybe_unused]] const cards::rank& dealer_card_value) -> bool
    {
        return false;
    }

    auto only_hit([[maybe_unused]] const std::vector<card>& hand, [[maybe_unused]] const cards::rank& dealer_card_value) -> bool
    {
        return true;
    }

    auto simple_strategy(const std::vector<card>& hand, const cards::rank& dealer_card_value) -> bool
    {
        const auto score = hand_score(hand);
        const auto ace = has_ace(hand);
        // if we have 11 or less with an ace we can treat the ace as 11 or 1 i.e. the hand is "soft"
        // if the ace going to 11 would bust us, the hand is "hard"
        const auto soft = ace and score != MAX_SCORE;

        // hit cases
        if (score <= 11 or (soft and score <= 17))
        {
            return true;
        }
        if (score == 12)
        {
            switch (dealer_card_value)
            {
                case cards::rank::TWO:
                case cards::rank::THREE:
                case cards::rank::SEVEN:
                case cards::rank::EIGHT:
                case cards::rank::NINE:
                case cards::rank::TEN:
                case cards::rank::JACK:
                case cards::rank::QUEEN:
                case cards::rank::KING:
                case cards::rank::ACE:
                    return true;
                default:
                    return false;
            }
        }
        if (score <= 16)
        {
            switch (dealer_card_value)
            {
                case cards::rank::SEVEN:
                case cards::rank::EIGHT:
                case cards::rank::NINE:
                case cards::rank::TEN:
                case cards::rank::JACK:
                case cards::rank::QUEEN:
                case cards::rank::KING:
                case cards::rank::ACE:
                    return true;
                default:
                    return false;
            }
        }
        if (not soft) // hard 17 or higher
        {
            return false;
        }
        if (ace and hand.size() == 2)
        {
            const auto non_ace = hand.at(0).r == cards::rank::ACE ? hand.at(1).r : hand.at(0).r;
            if (non_ace == cards::rank::EIGHT or non_ace == cards::rank::NINE)
            {
                return false;
            }
            if (non_ace == cards::rank::SEVEN)
            {
                switch (dealer_card_value)
                {
                    case cards::rank::NINE:
                    case cards::rank::TEN:
                    case cards::rank::JACK:
                    case cards::rank::QUEEN:
                    case cards::rank::KING:
                    case cards::rank::ACE:
                        return true;
                    default:
                        return false;
                }
            }
        }
        // if all of the above are false, we stay
        return false;
    }
} // namespace strategies