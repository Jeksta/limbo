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
        [](std::monostate value)
        {
            return "nullType";
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
        [](std::string value) -> int
        {
            return std::stoi(value);
        },
        [](std::monostate value) -> int
        {
            throw std::crash("cannot cast null to int");
        },
        [](auto &&value) -> int
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
        [](std::string value) -> double
        {
            return std::stod(value);
        },
        [](std::monostate value) -> double
        {
            throw std::crash("cannot cast null to double");
        },
        [](auto &&value) -> double
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
        [](std::string value) -> std::string
        {
            return value;
        },
        [](std::monostate value) -> std::string
        {
            return "null";
        },
        [](auto &&value) -> std::string
        {
            return std::to_string(value);
        },
    };

    return std::visit(type, value);
}

void interpreter::
    print(const interpreter::any &value)
{
    std::cout << interpreter::string_of(value) << "\n";
}
