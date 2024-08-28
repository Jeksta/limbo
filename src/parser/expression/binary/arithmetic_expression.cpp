#include "arithmetic_expression.hpp"

parser::arithmetic_expression::
    arithmetic_expression(parser::unique_expr left,
                          lexer::token arithmetic_operator,
                          parser::unique_expr right)
    : binary_expression(std::move(left), arithmetic_operator, std::move(right))
{
}

parser::arithmetic_expression::
    ~arithmetic_expression() {}

parser::any parser::arithmetic_expression::
    accept(const interpreter::expression_visitor *visitor) const
{
    return visitor->visit(this);
}

std::string parser::arithmetic_expression::
    to_string() const
{
    std::string right_str(right->to_string());
    std::string left_str(left->to_string());

    std::vector<std::string> str({
        "arithmetic",
        left_str,
        binary_operator.literal,
        right_str,
    });
    return std::parenthesize(str, " ", std::bracket::Square);
}