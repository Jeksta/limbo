#pragma once

#include "expression.hpp"

namespace parser
{

    struct binary_expression
        : public expression
    {
        unique_expr left;
        lexer::token binary_operator;
        unique_expr right;

        binary_expression(unique_expr left,
                          lexer::token binary_operator,
                          unique_expr right);
        ~binary_expression();

        parser::any accept(const interpreter::visitor *visitor) const;
        std::string to_string() const;
    };
} // namespace parser