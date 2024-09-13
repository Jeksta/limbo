#pragma once

#include "binary_expression.hpp"

namespace parser
{
    struct arithmetic_expression
        : public binary_expression
    {
        arithmetic_expression(parser::unique_expr left,
                              lexer::token arithmetic_operator,
                              parser::unique_expr right);
        ~arithmetic_expression();

        interpreter::any accept(const interpreter::expression_visitor *visitor) const;
        std::string to_string() const;
    };

} // namespace parser
