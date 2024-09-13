#include "compare_expression.hpp"

parser::compare_expression::
    compare_expression(std::unique_ptr<expression> left,
                        lexer::token compare_operator,
                        std::unique_ptr<expression> right)
    : binary_expression(std::move(left), compare_operator, std::move(right))
{
}

parser::compare_expression::
    ~compare_expression() {}

interpreter::any parser::compare_expression::
    accept(const interpreter::expression_visitor *visitor) const
{
    return visitor->visit(this);
}

std::string parser::compare_expression::
    to_string() const
{
    std::string right_str(right->to_string());
    std::string left_str(left->to_string());

    std::vector<std::string> str({
        "compare",
        left_str,
        binary_operator.literal,
        right_str,
    });
    return std::parenthesize(str, " ", std::bracket::Square);
}