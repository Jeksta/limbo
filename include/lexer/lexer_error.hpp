#pragma once

#include <exception>

namespace lexer
{
    class invalid_token : public std::exception
    {
    public:
        const char *what() const throw();
    };
} // namespace exc