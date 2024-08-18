#pragma once

#include <vector>
#include <string>

namespace std
{
    std::vector<std::string> split(const std::string &str, std::string delimiter);
    std::string join(const std::vector<std::string> &str, std::string delimiter);

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
