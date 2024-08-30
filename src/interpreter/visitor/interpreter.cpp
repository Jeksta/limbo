#include "interpreter.hpp"
#include "variant.hpp"
#include "binary_expression.hpp"
#include "compare_expression.hpp"
#include "arithmetic_expression.hpp"
#include "call_expression.hpp"

using namespace interpreter::error;

interpreter::interpreter::
    interpreter()
{
}

interpreter::interpreter::
    ~interpreter()
{
}

parser::any interpreter::interpreter::
    evaluate(const parser::expression *expr) const
{
    return expr->accept(this);
}

parser::any interpreter::interpreter::
    visit(const parser::variant *variant) const
{
    return variant->value;
}

parser::any interpreter::interpreter::
    visit(const parser::binary_expression *binary) const
{
    throw error::runtime_crash();
}

parser::any interpreter::interpreter::
    visit(const parser::arithmetic_expression *arithmetic) const
{
    parser::any left(this->evaluate(arithmetic->left.get()));
    parser::any right(this->evaluate(arithmetic->right.get()));

    const lexer::token &token = arithmetic->binary_operator;

    auto overload = parser::overload{
        [&token](auto &&left, std::string right) -> parser::any
        {
            throw unsupported_operator(token.literal, type_of(left), type_of(right));
        },
        [&token](std::string left, auto &&right) -> parser::any
        {
            throw unsupported_operator(token.literal, type_of(left), type_of(right));
        },
        [&token](std::string left, std::string right) -> parser::any
        {
            switch (token.type)
            {
            case lexer::Plus:
                return left + right;

            default:
                throw unsupported_operator(token.literal, type_of(left), type_of(right));
            }
        },
        [&token](auto &&left, auto &&right) -> parser::any
        {
            switch (token.type)
            {
            case lexer::Plus:
                return left + right;
            case lexer::Dash:
                return left - right;
            case lexer::Star:
                return left * right;
            case lexer::Slash:
            {
                if (right == 0){
                    throw arithmetic_crash("dividing by zero");
                }
                return left / right;
            }

            default:
                throw unsupported_operator(token.literal, type_of(left), type_of(right));
            }
        },
    };
    return std::visit(overload, left, right);
}

parser::any interpreter::interpreter::
    visit(const parser::compare_expression *compare) const
{
    parser::any left(this->evaluate(compare->left.get()));
    parser::any right(this->evaluate(compare->right.get()));

    const lexer::token &token = compare->binary_operator;

    auto overload = parser::overload{
        [&token](auto &&left, std::string right) -> bool
        {
            throw unsupported_operator(token.literal, type_of(left), type_of(right));
        },
        [&token](std::string left, auto &&right) -> bool
        {
            throw unsupported_operator(token.literal, type_of(left), type_of(right));
        },
        [&token](std::string left, std::string right) -> bool
        {
            switch (token.type)
            {
            case lexer::EqualEqual:
                return left == right;

            case lexer::ExclamationMarkEqual:
                return left != right;

            default:
                throw unsupported_operator(token.literal, type_of(left), type_of(right));
            }
        },
        [&token](auto &&left, auto &&right) -> bool
        {
            switch (token.type)
            {
            case lexer::EqualEqual:
                return left == right;

            case lexer::ExclamationMarkEqual:
                return left != right;

            case lexer::GreaterThan:
                return left > right;

            case lexer::GreaterThanEqual:
                return left >= right;

            case lexer::LessThan:
                return left < right;

            case lexer::LessThanEqual:
                return left <= right;

            default:
                throw unsupported_operator(token.literal, type_of(left), type_of(right));
            }
        },
    };
    return std::visit(overload, left, right);
}

parser::any interpreter::interpreter::
    visit(const parser::call_expression *call) const
{
    parser::any expr(this->evaluate(call->parameter.get()));

    const lexer::token &id = call->identifier;
    switch (id.type)
    {
    case lexer::TypeOf:
        return type_of(expr);

    case lexer::BoolCast:
        return bool_of(expr);

    case lexer::IntCast:
        return int_of(expr);

    case lexer::DoubleCast:
        return double_of(expr);

    case lexer::StringCast:
        return string_of(expr);
    }

    throw runtime_crash("unknown call");
}

parser::any interpreter::interpreter::
    interpret(const parser::expression *expr) const
{
    return this->evaluate(expr);
}
