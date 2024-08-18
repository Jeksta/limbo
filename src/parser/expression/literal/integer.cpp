#include "integer.hpp"

parser::integer::
    integer(int value)
    : variant(value)
{
}
parser::integer::
    ~integer()
{
}

parser::any parser::integer::
    accept(const interpreter::visitor *visitor) const
{
    return visitor->visit_integer(this);
}

std::string parser::integer::
    to_string() const
{
    int v = std::get<int>(value);
    return std::parenthesize({"int", std::to_string(v)}, " ", std::bracket::Round);
}