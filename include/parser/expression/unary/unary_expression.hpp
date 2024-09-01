#pragma once

#include "expression.hpp"

namespace parser
{
    struct unary_expression
        : public expression
    {
        lexer::token unary_operator;
        std::unique_ptr<expression> right;

    public:
        unary_expression(lexer::token unary_operator,
                         std::unique_ptr<expression> right);
        ~unary_expression();

        interpreter::any accept(const interpreter::expression_visitor *visitor) const;
        std::string to_string() const;
    };
} // namespace parser
