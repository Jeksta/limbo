#include "boolean.hpp"

parser::boolean::
    boolean(bool value)
    : variant(value)
{
}
parser::boolean::
    ~boolean()
{
}

parser::any parser::boolean::
    accept(const interpreter::visitor *visitor) const
{
    throw std::not_implemented();
}

std::string parser::boolean::
    to_string() const
{
    int v = std::get<bool>(value);
    return std::parenthesize({"bool", std::to_string(v)}, " ", std::bracket::Round);
}