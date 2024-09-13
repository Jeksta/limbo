#include "stdlib.hpp"

std::string interpreter::
    type_of(const interpreter::any &value)
{
    auto type = interpreter::overload{
        [](bool value)
        {
            return "bool";
        },
        [](int value)
        {
            return "int";
        },
        [](double value)
        {
            return "double";
        },
        [](std::string value)
        {
            return "string";
        },
    };

    return std::visit(type, value);
}

bool interpreter::
    bool_of(const interpreter::any &value)
{
    return is_truthy(value);
}

int interpreter::
    int_of(const interpreter::any &value)
{
    auto type = interpreter::overload{
        [](std::string value)
        {
            return std::stoi(value);
        },
        [](auto value)
        {
            return (int)value;
        },
    };

    return std::visit(type, value);
}

double interpreter::
    double_of(const interpreter::any &value)
{
    auto type = interpreter::overload{
        [](std::string value)
        {
            return std::stod(value);
        },
        [](auto value)
        {
            return (double)value;
        },
    };

    return std::visit(type, value);
}

std::string interpreter::
    string_of(const interpreter::any &value)
{
    auto type = interpreter::overload{
        [](std::string value)
        {
            return value;
        },
        [](auto value)
        {
            return std::to_string(value);
        },
    };

    return std::visit(type, value);
}