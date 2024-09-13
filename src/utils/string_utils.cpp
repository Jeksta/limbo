#include "string_utils.hpp"

std::vector<std::string> std::
    split(const std::string &str, std::string delimiter)
{
    std::vector<std::string> parse = std::vector<std::string>();

    size_t prev_pos = 0;
    size_t next_pos = 0;
    std::string token;
    while ((next_pos = str.find(delimiter, prev_pos)) != std::string::npos)
    {
        token = str.substr(prev_pos, next_pos - prev_pos);
        prev_pos = next_pos + delimiter.length();
        parse.push_back(token);
    }

    parse.push_back(str.substr(prev_pos));
    return parse;
}

std::string std::
    join(const std::vector<std::string> &str, std::string delimiter)
{
    std::string result("");

    for (std::vector<std::string>::const_iterator it = str.begin(); it != std::prev(str.end()); ++it)
    {
        result += *it + delimiter;
    }

    return result + str.back();
}

bool std::
    ends_with(const std::string_view &str, const std::string_view &suffix)
{
    return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool std::
    starts_with(const std::string_view &str, const std::string_view &prefix)
{
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}

std::string std::
    remove_chars(std::string str, const std::string &chars)
{
    for (unsigned int i = 0; i < chars.length(); ++i)
    {
        str.erase(remove(str.begin(), str.end(), chars.at(i)), str.end());
    }

    return str;
}

std::string std::
    parenthesize(const std::vector<std::string> &str,
                 std::string delimiter,
                 std::bracket bracket)
{
    std::string result(std::join(str, delimiter));

    switch (bracket)
    {
    case std::bracket::Round:
        return "(" + result + ")";
    case std::bracket::Square:
        return "[" + result + "]";
    case std::bracket::Curly:
        return "{" + result + "}";

    default:
        return result;
    }
}