#pragma once

#include "error.hpp"

namespace scanner::error
{
    class scanner_crash
        : public std::crash
    {
    public:
        scanner_crash();
        scanner_crash(std::string message);
    };

    class file_not_found
        : public scanner_crash
    {
    public:
        file_not_found(std::string path);
    };
} // namespace scanner:error
