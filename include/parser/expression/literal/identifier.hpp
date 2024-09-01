#pragma once

#include "literal.hpp"

namespace parser
{
    struct identifier
        : public literal<std::string>
    {
        identifier(std::string name);
        ~identifier();

        interpreter::any accept(const interpreter::expression_visitor *visitor) const;
        std::string to_string() const;
    };

} // namespace parser
