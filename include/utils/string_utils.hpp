#pragma once

#include <vector>
#include <string>
#include <algorithm>

namespace std
{
    std::vector<std::string> split(const std::string &str, std::string delimiter);
    std::string join(const std::vector<std::string> &str, std::string delimiter);
    bool ends_with(const std::string_view &str, const std::string_view &suffix);
    bool starts_with(const std::string_view &str, const std::string_view &prefix);
    std::string remove_chars(std::string str, const std::string &chars);

    enum bracket
    {
        None,
        Round,
        Square,
        Curly
    };
    std::string parenthesize(const std::vector<std::string> &str,
                             std::string delimiter,
                             bracket bracket = bracket::Round);
} // namespace std
