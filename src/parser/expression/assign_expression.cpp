#include "assign_expression.hpp"

parser::assign_expression::
    assign_expression(lexer::token identifier,
                      parser::unique_expr right)
    : identifier(identifier), right(std::move(right))
{
}

parser::assign_expression::
    ~assign_expression()
{
}

interpreter::any parser::assign_expression::
    accept(const interpreter::expression_visitor *visitor) const
{
    return visitor->visit(this);
}

std::string parser::assign_expression::
    to_string() const
{
    std::string right_str(right->to_string());

    std::vector<std::string> str({
        "assign",
        right_str,
        "to",
        identifier.literal,
    });
    return std::parenthesize(str, " ", std::bracket::Square);
}