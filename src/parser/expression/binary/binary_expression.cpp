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

parser::any parser::binary_expression::
    accept(const interpreter::visitor *visitor) const
{
    return visitor->visit_binary_expression(this);
}

std::string parser::binary_expression::
    to_string() const
{
    std::string right_str(right->to_string());
    std::string left_str(left->to_string());

    std::vector<std::string> str({
        "binary",
        right_str,
        binary_operator.literal,
        left_str,
    });
    return std::parenthesize(str, " ", std::bracket::Square);
}