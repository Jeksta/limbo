#pragma once

#include <variant>
#include <string>

namespace parser
{
    template <class... Ts>
    struct overload : Ts...
    {
        using Ts::operator()...;
    };
    template <class... Ts>
    overload(Ts...) -> overload<Ts...>;

    typedef std::variant<int, bool, double, std::string> any;
} // namespace parser
