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

    bool is_truthy(const any &value);
    std::string type_of(const any &value);
} // namespace parser
