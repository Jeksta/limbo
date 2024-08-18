#pragma once

#include "binary_expression.hpp"

namespace parser
{
    struct equality_expression
        : public binary_expression
    {
        equality_expression(std::unique_ptr<expression> left,
                            lexer::token equality_operator,
                            std::unique_ptr<expression> right)
            : binary_expression(std::move(left), equality_operator, std::move(right))
        {
        }
        ~equality_expression();

        parser::any accept(const interpreter::visitor *visitor) const
        {
            return visitor->visit_equality_expression(this);
        }
    };

} // namespace parser
