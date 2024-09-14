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

        void accept(interpreter::expression_visitor *visitor);
        std::string to_string() const;
    };
} // namespace parser