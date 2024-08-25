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

#include <memory>
#include <stack>
#include "any.hpp"
#include "token.hpp"
#include "parser_error.hpp"

namespace interpreter
{
    class visitor
    {
    public:
        virtual parser::any visit(const parser::variant *integer) const = 0;
        virtual parser::any visit(const parser::binary_expression *binary) const = 0;
        virtual parser::any visit(const parser::equality_expression *equal) const = 0;
        virtual parser::any visit(const parser::call_expression *call) const = 0;
    };

    class interpreter : public visitor
    {
        std::unique_ptr<std::stack<int>> memory;

    private:
        parser::any evaluate(const parser::expression *expr) const;

    public:
        interpreter();
        ~interpreter();

        parser::any visit(const parser::variant *variant) const;
        parser::any visit(const parser::binary_expression *binary) const;
        parser::any visit(const parser::equality_expression *equal) const;
        parser::any visit(const parser::call_expression *call) const;

        parser::any interpret(const parser::expression *expr) const;
    };

    class interpretable
    {
    public:
        virtual parser::any accept(const visitor *visitor) const = 0;
    };

} // namespace interpreter
