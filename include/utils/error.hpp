#pragma once

#include <iostream>
#include <string>
#include <exception>

namespace std
{
    class crash
        : public exception
    {
    protected:
        std::string message = "crash";

    public:
        crash();
        crash(std::string message);

        const char *what() const throw();
    };

    class not_implemented
        : public exception
    {
    public:
        const char *what() const throw();
    };

    static void report(int line, std::string where, std::string message);
    static void error(int line, std::string message);
} // namespace std
