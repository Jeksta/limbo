#pragma once

#include "expression.hpp"

namespace parser
{
    struct assign_expression
        : public expression
    {
        lexer::token identifier;
        unique_expr right;

        assign_expression(lexer::token identifier,
                          unique_expr right);
        ~assign_expression();

        void accept(interpreter::expression_visitor *visitor);
        std::string to_string() const;
    };

} // namespace parser
