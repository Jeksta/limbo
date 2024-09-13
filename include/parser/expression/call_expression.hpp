#pragma once

#include "expression.hpp"

namespace parser
{
    struct call_expression
        : public expression
    {
        lexer::token identifier;
        // TODO calls only take one param at the moment
        unique_expr parameter;

        call_expression(lexer::token identifier,
                        unique_expr parameter);
        ~call_expression();

        interpreter::any accept(const interpreter::expression_visitor *visitor) const;
        std::string to_string() const;
    };
} // namespace parser
