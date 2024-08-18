#include "io_stream.hpp"

void std::print(const std::vector<std::string> &str)
{
    for (const std::string &text : str)
    {
        std::cout << text << " ";
    }
    std::cout << "\n";
}

void std::print_debug_message(std::string module,
                              std::string message)
{
    std::cout << "> [debug::" + module + "]: " + message + "\n";
}

void std::print_debug_message(std::string module,
                              const std::vector<std::string> &str)
{
    std::string result(std::join(str, " "));
    std::cout << "> [debug::" + module + "]: " + result + "\n";
}