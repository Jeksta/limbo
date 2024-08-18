#pragma once

#include <iostream>
#include <string>
#include <exception>

namespace std
{
    class not_implemented : public exception
    {
    public:
        const char *what() const throw();
    };

    static void report(int line, std::string where, std::string message);
    static void error(int line, std::string message);
} // namespace std
