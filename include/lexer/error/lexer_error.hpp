#pragma once

#include "error.hpp"

namespace lexer::error
{
    class invalid_token
        : public std::crash
    {
    public:
        invalid_token();
    };
} // namespace exc