#include "util.hpp"

#include <iostream>

namespace util
{
    auto log(std::ostream* os_ptr, std::string_view s) -> void
    {
        if (os_ptr)
        {
            *os_ptr << s;
        }
    }
}// namespace util