#pragma once

#include "expression.hpp"

namespace parser
{
    struct call_expression
        : public expression
    {
        lexer::token identifier;
        unique_expr parameter;

        call_expression(lexer::token identifier,
                        unique_expr parameter);
        ~call_expression();

        parser::any accept(const interpreter::visitor *visitor) const;
        std::string to_string() const;
    };
} // namespace parser
