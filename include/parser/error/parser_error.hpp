#pragma once

#include "error.hpp"

namespace parser::error
{
    class parser_crash
        : public std::crash
    {
    public:
        parser_crash();
        parser_crash(std::string message);
    };
} // namespace parser
