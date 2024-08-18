#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "string_utils.hpp"

namespace std
{
    void print(const std::vector<std::string> &str);
    void print_debug_message(std::string module,
                             std::string message);
    void print_debug_message(std::string module,
                             const std::vector<std::string> &str);
} // namespace lexer
