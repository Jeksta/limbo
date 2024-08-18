#include "bool.hpp"

parser::bool::
    bool(bool value)
    : variant(value)
{
}
parser::bool::
    ~bool()
{
}

parser::any parser::bool::
    accept(const interpreter::visitor *visitor) const
{
    return visitor->visit_integer(this);
}

std::string parser::bool::
    to_string() const
{
    int v = std::get<bool>(value);
    return std::parenthesize({"bool", std::to_string(v)}, " ", std::bracket::Round);
}