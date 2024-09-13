#pragma once

// forward declare
namespace parser
{
    class expression;

    class unary_expression;
    class compare_expression;
    class arithmetic_expression;
    class call_expression;
    class binary_expression;

    class variant;
    class identifier;
}

#include "any.hpp"

namespace interpreter
{
    class expression_visitor
    {
    public:
        virtual any visit(const parser::variant *integer) const = 0;
        virtual any visit(const parser::identifier *identifier) const = 0;

        virtual any visit(const parser::unary_expression *unary) const = 0;

        virtual any visit(const parser::binary_expression *binary) const = 0;
        virtual any visit(const parser::compare_expression *compare) const = 0;
        virtual any visit(const parser::arithmetic_expression *arithmetic) const = 0;

        virtual any visit(const parser::call_expression *call) const = 0;
        virtual any visit(const parser::assign_expression *assign) const = 0;
    };

    class interpretable
    {
    public:
        virtual any accept(const expression_visitor *visitor) const = 0;
    };
} // namespace interpreter