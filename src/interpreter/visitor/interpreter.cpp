#include "interpreter.hpp"
#include "variant.hpp"
#include "identifier.hpp"
#include "unary_expression.hpp"
#include "binary_expression.hpp"
#include "compare_expression.hpp"
#include "arithmetic_expression.hpp"
#include "call_expression.hpp"
#include "assign_expression.hpp"

using namespace interpreter::error;

interpreter::interpreter::
    interpreter(std::string scope)
    : current_scope(scope),
      runtime_environment(storage::runtime_environment::get_instance())
{
}

interpreter::interpreter::
    ~interpreter()
{
}

interpreter::any interpreter::interpreter::
    evaluate(const parser::expression *expr) const
{
    return expr->accept(this);
}

interpreter::any interpreter::interpreter::
    visit(const parser::variant *variant) const
{
    return variant->value;
}

interpreter::any interpreter::interpreter::
    visit(const parser::identifier *identifier) const
{
    return runtime_environment.get_variable(current_scope, identifier->value);
}

interpreter::any interpreter::interpreter::
    visit(const parser::unary_expression *unary) const
{
    any right(this->evaluate(unary->right.get()));
    const lexer::token token = unary->unary_operator;

    auto unary_visitor = overload{
        [&token](auto &&right) -> any
        {
            return right * -1;
        },
        [&token](std::string right) -> any
        {
            throw unsupported_operator(token.literal, type_of(right), type_of(right));
        },
    };

    switch (token.type)
    {
    case lexer::ExclamationMark:
        return !is_truthy(right);
    case lexer::Plus:
        return right;
    case lexer::Dash:
        return std::visit(unary_visitor, right);

    default:
        throw unsupported_operator(token.literal, type_of(right), type_of(right));
    }
}

interpreter::any interpreter::interpreter::
    visit(const parser::binary_expression *binary) const
{
    throw error::runtime_crash("No fallback for binary expression");
}

interpreter::any interpreter::interpreter::
    visit(const parser::arithmetic_expression *arithmetic) const
{
    any left(this->evaluate(arithmetic->left.get()));
    any right(this->evaluate(arithmetic->right.get()));

    const lexer::token &token = arithmetic->binary_operator;

    auto arith_visitor = overload{
        [&token](auto &&left, std::string right) -> any
        {
            throw unsupported_operator(token.literal, type_of(left), type_of(right));
        },
        [&token](std::string left, auto &&right) -> any
        {
            throw unsupported_operator(token.literal, type_of(left), type_of(right));
        },
        [&token](std::string left, std::string right) -> any
        {
            switch (token.type)
            {
            case lexer::Plus:
                return left + right;

            default:
                throw unsupported_operator(token.literal, type_of(left), type_of(right));
            }
        },
        [&token](auto &&left, auto &&right) -> any
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
                if (right == 0)
                {
                    throw arithmetic_crash("dividing by zero");
                }
                return left / right;
            }

            default:
                throw unsupported_operator(token.literal, type_of(left), type_of(right));
            }
        },
    };
    return std::visit(arith_visitor, left, right);
}

interpreter::any interpreter::interpreter::
    visit(const parser::compare_expression *compare) const
{
    any left(this->evaluate(compare->left.get()));
    any right(this->evaluate(compare->right.get()));

    const lexer::token &token = compare->binary_operator;

    auto o = overload{
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
    return std::visit(o, left, right);
}

interpreter::any interpreter::interpreter::
    visit(const parser::call_expression *call) const
{
    any expr(this->evaluate(call->parameter.get()));

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

interpreter::any interpreter::interpreter::
    visit(const parser::assign_expression *assignment) const
{
    std::string id(assignment->identifier.literal);
    any value(this->evaluate(assignment->right.get()));

    runtime_environment.set_variable(current_scope, id, value);
    return value;
}

interpreter::any interpreter::interpreter::
    interpret(const parser::expression *expr) const
{
    return this->evaluate(expr);
}
