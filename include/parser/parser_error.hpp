#pragma once

#include <exception>

namespace parser
{
    class parser_error : public std::exception
    {
    public:
        const char *what() const throw();
    };
} // namespace parser
