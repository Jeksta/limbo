#pragma once

#include "binary_expression.hpp"

namespace parser
{
    struct equality_expression
        : public binary_expression
    {
        equality_expression(std::unique_ptr<expression> left,
                            lexer::token equality_operator,
                            std::unique_ptr<expression> right);
        ~equality_expression();

        parser::any accept(const interpreter::visitor *visitor) const;
        std::string to_string() const;
    };

} // namespace parser
