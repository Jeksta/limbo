#pragma once

#include "expression.hpp"

namespace parser
{

    struct binary_expression
        : public expression
    {
        std::unique_ptr<expression> left;
        lexer::token binary_operator;
        std::unique_ptr<expression> right;

        binary_expression(std::unique_ptr<expression> left,
                          lexer::token binary_operator,
                          std::unique_ptr<expression> right);
        ~binary_expression();

        parser::any accept(const interpreter::visitor *visitor) const;
        std::string to_string() const;
    };
} // namespace parser