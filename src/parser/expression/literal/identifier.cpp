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

void parser::identifier::
    accept(interpreter::expression_visitor *visitor)
{
    visitor->visit(this);
}

std::string parser::identifier::
    to_string() const
{
    return std::parenthesize({"identifier", value}, " ", std::bracket::Round);
}