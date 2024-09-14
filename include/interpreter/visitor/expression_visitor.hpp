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
        virtual void visit(const parser::variant *integer) = 0;
        virtual void visit(const parser::identifier *identifier) = 0;
        virtual void visit(const parser::unary_expression *unary) = 0;
        virtual void visit(const parser::binary_expression *binary) = 0;
        virtual void visit(const parser::compare_expression *compare) = 0;
        virtual void visit(const parser::arithmetic_expression *arithmetic) = 0;
        virtual void visit(const parser::call_expression *call) = 0;
        virtual void visit(const parser::assign_expression *assign) = 0;
    };

    class interpretable
    {
    public:
        virtual void accept(expression_visitor *visitor) = 0;
    };
} // namespace interpreter