#include "error.hpp"

std::crash::crash() {}
std::crash::crash(std::string message) : message(message) {}

const char *std::crash::
    what() const throw()
{
    return message.c_str();
}

const char *std::not_implemented::
    what() const throw()
{
    return "Not implemented yet";
}

static void std::
    report(int line, std::string where, std::string message)
{
    std::cerr << "[line " + std::to_string(line) + "] Error" + where + ": " + message << std::endl;
}

static void std::
    error(int line, std::string message)
{
    std::report(line, "", message);
}