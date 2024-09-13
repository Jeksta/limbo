#include "identifier.hpp"

parser::identifier::
    identifier(std::string name)
    : literal(name)
{
}

parser::identifier::
    ~identifier()
{
}

interpreter::any parser::identifier::
    accept(const interpreter::expression_visitor *visitor) const
{
    return visitor->visit(this);
}

std::string parser::identifier::
    to_string() const
{
    return std::parenthesize({"identifier", value}, " ", std::bracket::Round);
}