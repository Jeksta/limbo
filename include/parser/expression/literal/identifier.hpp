#pragma once

#include "literal.hpp"

namespace parser
{
    struct identifier
        : public literal<std::string>
    {
        identifier(std::string name);
        ~identifier();

        void accept(interpreter::expression_visitor *visitor);
        std::string to_string() const;
    };

} // namespace parser
