#include "equality_expression.hpp"

parser::equality_expression::
    equality_expression(std::unique_ptr<expression> left,
                        lexer::token equality_operator,
                        std::unique_ptr<expression> right)
    : binary_expression(std::move(left), equality_operator, std::move(right))
{
}

parser::equality_expression::
    ~equality_expression() {}

parser::any parser::equality_expression::
    accept(const interpreter::visitor *visitor) const
{
    return visitor->visit(this);
}

std::string parser::equality_expression::
    to_string() const
{
    std::string right_str(right->to_string());
    std::string left_str(left->to_string());

    std::vector<std::string> str({
        "equals",
        right_str,
        binary_operator.literal,
        left_str,
    });
    return std::parenthesize(str, " ", std::bracket::Square);
}