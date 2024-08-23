#pragma once

// forward declare
namespace parser
{
    class expression;

    class binary_expression;
    class equality_expression;

    class integer;
    class boolean;
}

#include <memory>
#include <variant>
#include <stack>
#include "any.hpp"
#include "token.hpp"
#include "parser_error.hpp"

namespace interpreter
{
    template <typename T>
    struct equality
    {
        const T left;
        const T right;

        equality(T left, T right)
            : left(left), right(right) {}

        bool resolve(const lexer::token_type &type)
        {
            switch (type)
            {
            case lexer::EqualEqual:
                return left == right;
            case lexer::ExclamationMarkEqual:
                return left != right;

            default:
                throw parser::parser_error();
            }
        }
    };

    class visitor
    {
    public:
        virtual parser::any visit(const parser::integer *integer) const = 0;
        virtual parser::any visit(const parser::boolean *boolean) const = 0;
        virtual parser::any visit(const parser::binary_expression *binary) const = 0;
        virtual parser::any visit(const parser::equality_expression *equal) const = 0;
    };

    class interpreter : public visitor
    {
        std::unique_ptr<std::stack<int>> memory;

    private:
        parser::any evaluate(const parser::expression *expr) const;

        template <class... Ts>
        struct overload : Ts...
        {
            using Ts::operator()...;
        };
        template <class... Ts>
        overload(Ts...) -> overload<Ts...>;

    public:
        interpreter();
        ~interpreter();

        static bool is_truthy(parser::any value);

        parser::any visit(const parser::integer *integer) const;
        parser::any visit(const parser::boolean *boolean) const;
        parser::any visit(const parser::binary_expression *binary) const;
        parser::any visit(const parser::equality_expression *equal) const;

        parser::any interpret(const parser::expression *expr) const;
    };

    class interpretable
    {
    public:
        virtual parser::any accept(const visitor *visitor) const = 0;
    };

} // namespace interpreter
