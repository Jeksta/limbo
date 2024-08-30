#pragma once

#include "error.hpp"
#include "token.hpp"

namespace lexer::error
{
    class invalid_token
        : public std::crash
    {
    public:
        invalid_token(const lexer::token &token);
    };
} // namespace lexer::error