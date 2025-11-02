#ifndef BLACKJACK_UTIL_HPP
#define BLACKJACK_UTIL_HPP

#include "deck.hpp"

#include <ranges>
#include <string>
#include <utility>

namespace util
{
    template <typename Enum>
    constexpr auto iterate_enum(Enum first, Enum last) {
        return std::views::iota(std::to_underlying(first), std::to_underlying(last))
           | std::views::transform([](auto e) { return static_cast<Enum>(e); });
    }

    auto get_compact_deck_string(const deck& d) -> std::string;

    auto log(std::ostream& os, std::string_view s) -> void;
} // namespace util

#endif //BLACKJACK_UTIL_HPP