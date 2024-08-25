#include "boollib.hpp"

bool interpreter::
    is_truthy(const parser::any &value)
{
    auto truthy = parser::overload{
        [](bool value) -> bool
        {
            return value;
        },
        [](int value) -> bool
        {
            return value == 0 ? false : true;
        },
        [](double value) -> bool
        {
            return value == 0.0 ? false : true;
        },
        [](std::string value) -> bool
        {
            return value.size() > 0;
        },
    };

    return std::visit(truthy, value);
}