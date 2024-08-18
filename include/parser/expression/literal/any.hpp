#pragma once

#include <variant>

namespace parser
{
    enum type
    {
        Int,
        Bool
    };

    typedef std::variant<int, bool> any;
} // namespace parser
