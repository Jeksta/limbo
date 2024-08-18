#pragma once

// forward declare
namespace parser
{
    class expression;

    class binary_expression;
    class equality_expression;

    class integer;
}

#include <memory>
#include <variant>
#include <stack>
#include "any.hpp"

namespace interpreter
{
    class visitor
    {
    public:
        virtual parser::any visit_integer(const parser::integer *integer) const = 0;
        virtual parser::any visit_binary_expression(const parser::binary_expression *expr) const = 0;
        virtual parser::any visit_equality_expression(const parser::equality_expression *expr) const = 0;
    };

    class interpreter : public visitor
    {
        std::unique_ptr<std::stack<int>> memory;

    private:
        parser::any evaluate(const parser::expression *expr) const;
        bool is_truthy();

    public:
        interpreter();
        ~interpreter();

        parser::any visit_integer(const parser::integer *integer) const;

        parser::any visit_binary_expression(const parser::binary_expression *expr) const;
        parser::any visit_equality_expression(const parser::equality_expression *expr) const;

        parser::any interpret(const parser::expression *expr) const;
    };

    class interpretable
    {
    public:
        virtual parser::any accept(const visitor *visitor) const = 0;
    };

} // namespace interpreter
