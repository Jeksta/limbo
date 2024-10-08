#include "unary_expression.hpp"

parser::unary_expression::
    unary_expression(lexer::token unary_operator,
                     std::unique_ptr<parser::expression> right)
    : unary_operator(unary_operator), right(std::move(right))
{
}

parser::unary_expression::
    ~unary_expression()
{
}

void parser::unary_expression::
    accept(interpreter::expression_visitor *visitor)
{
    visitor->visit(this);
}

std::string parser::unary_expression::
    to_string() const
{
    std::string right_str(right->to_string());

    std::vector<std::string> str({
        "unary",
        unary_operator.literal,
        right_str,
    });
    return std::parenthesize(str, " ", std::bracket::Square);
}