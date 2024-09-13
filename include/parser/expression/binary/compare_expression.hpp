#pragma once

#include "binary_expression.hpp"

namespace parser
{
    struct compare_expression
        : public binary_expression
    {
        compare_expression(parser::unique_expr left,
                           lexer::token compare_operator,
                           parser::unique_expr right);
        ~compare_expression();

        interpreter::any accept(const interpreter::expression_visitor *visitor) const;
        std::string to_string() const;
    };

} // namespace parser
