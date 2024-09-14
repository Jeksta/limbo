#include "binary_expression.hpp"

parser::binary_expression::
    binary_expression(std::unique_ptr<expression> left,
                      lexer::token binary_operator,
                      std::unique_ptr<expression> right)
    : left(std::move(left)), binary_operator(binary_operator), right(std::move(right))
{
}

parser::binary_expression::
    ~binary_expression()
{
}

void parser::binary_expression::
    accept(interpreter::expression_visitor *visitor)
{
    visitor->visit(this);
}

std::string parser::binary_expression::
    to_string() const
{
    std::string right_str(right->to_string());
    std::string left_str(left->to_string());

    std::vector<std::string> str({
        "binary",
        left_str,
        binary_operator.literal,
        right_str,
    });
    return std::parenthesize(str, " ", std::bracket::Square);
}