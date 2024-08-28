#pragma once

#include "error.hpp"

namespace interpreter::error
{
    class runtime_crash
        : public std::crash
    {
    public:
        runtime_crash();
        runtime_crash(std::string message);
    };

    class unsupported_operator
        : public runtime_crash
    {
    public:
        unsupported_operator(std::string op, std::string ltype, std::string rtype);
    };

    class arithmetic_crash
        : public runtime_crash
    {
    public:
        arithmetic_crash(std::string message);
    };
} // namespace interpreter::error
