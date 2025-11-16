#ifndef BLACKJACK_UTIL_HPP
#define BLACKJACK_UTIL_HPP

#include <ranges>
#include <utility>

namespace util
{
    template <typename Enum>
    constexpr auto iterate_enum(Enum first, Enum last) {
        return std::views::iota(std::to_underlying(first), std::to_underlying(last))
           | std::views::transform([](auto e) { return static_cast<Enum>(e); });
    }

    auto log(std::ostream* os, std::string_view s) -> void;
} // namespace util

#endif //BLACKJACK_UTIL_HPP