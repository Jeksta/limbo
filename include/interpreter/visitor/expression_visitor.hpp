#pragma once

// forward declare
namespace parser
{
    class expression;

    class binary_expression;
    class equality_expression;
    class call_expression;

    class variant;
}

#include "any.hpp"

namespace interpreter
{
    class expression_visitor
    {
    public:
        virtual parser::any visit(const parser::variant *integer) const = 0;
        virtual parser::any visit(const parser::binary_expression *binary) const = 0;
        virtual parser::any visit(const parser::equality_expression *equal) const = 0;
        virtual parser::any visit(const parser::call_expression *call) const = 0;
    };

    class interpretable
    {
    public:
        virtual parser::any accept(const expression_visitor *visitor) const = 0;
    };
} // namespace interpreter