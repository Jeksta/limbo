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
    evaluate(parser::expression *expr)
{
    expr->accept(this);
    return result;
}

void interpreter::interpreter::
    visit(const parser::variant *variant)
{
    result = variant->value;
}

void interpreter::interpreter::
    visit(const parser::identifier *identifier)
{
    result = runtime_environment.get_variable(current_scope, identifier->value);
}

void interpreter::interpreter::
    visit(const parser::unary_expression *unary)
{
    any right(this->evaluate(unary->right.get()));

    const lexer::token token = unary->unary_operator;

    auto unary_visitor = overload{
        [&token](auto &&right) -> any
        {
            switch (token.type)
            {
            case lexer::ExclamationMark:
                return !is_truthy(right);
            case lexer::Dash:
                return right * -1;

            default:
                throw unsupported_operator(token.literal, type_of(right), type_of(right));
            }
        },
        [&token](std::string right) -> any
        {
            throw unsupported_operator(token.literal, type_of(right), type_of(right));
        },
        [&token](std::monostate right) -> any
        {
            switch (token.type)
            {
            case lexer::ExclamationMark:
                return !is_truthy(right);

            default:
                throw unsupported_operator(token.literal, type_of(right), type_of(right));
            }
        },
    };

    switch (token.type)
    {
    case lexer::ExclamationMark:
        result = !is_truthy(right);
        break;

    case lexer::Plus:
        result = right;
        break;

    case lexer::Dash:
        result = std::visit(unary_visitor, right);
        break;

    default:
        throw unsupported_operator(token.literal, type_of(right), type_of(right));
    }
}

void interpreter::interpreter::
    visit(const parser::binary_expression *binary)
{
    throw error::runtime_crash("No fallback for binary expression");
}

void interpreter::interpreter::
    visit(const parser::arithmetic_expression *arithmetic)
{
    any left(this->evaluate(arithmetic->left.get()));
    any right(this->evaluate(arithmetic->right.get()));

    const lexer::token &token = arithmetic->binary_operator;

    auto arith_visitor = overload{
        [&token](std::monostate left, std::string right) -> any
        {
            throw unsupported_operator(token.literal, type_of(left), type_of(right));
        },
        [&token](std::string right, std::monostate left) -> any
        {
            throw unsupported_operator(token.literal, type_of(left), type_of(right));
        },
        // string
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
        // null
        [&token](auto &&left, std::monostate right) -> any
        {
            throw unsupported_operator(token.literal, type_of(left), type_of(right));
        },
        [&token](std::monostate left, auto &&right) -> any
        {
            throw unsupported_operator(token.literal, type_of(left), type_of(right));
        },
        [&token](std::monostate left, std::monostate right) -> any
        {
            throw unsupported_operator(token.literal, type_of(left), type_of(right));
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

    result = std::visit(arith_visitor, left, right);
}

void interpreter::interpreter::
    visit(const parser::compare_expression *compare)
{
    any left(this->evaluate(compare->left.get()));
    any right(this->evaluate(compare->right.get()));

    const lexer::token &token = compare->binary_operator;

    auto compare_override = overload{
        [&token](std::monostate left, std::string right) -> bool
        {
            throw unsupported_operator(token.literal, type_of(left), type_of(right));
        },
        [&token](std::string right, std::monostate left) -> bool
        {
            throw unsupported_operator(token.literal, type_of(left), type_of(right));
        },
        // string
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
        // null
        [&token](auto &&left, std::monostate right) -> bool
        {
            switch (token.type)
            {
            case lexer::EqualEqual:
                return false;

            case lexer::ExclamationMarkEqual:
                return true;

            default:
                throw unsupported_operator(token.literal, type_of(left), type_of(right));
            }
        },
        [&token](std::monostate left, auto &&right) -> bool
        {
            switch (token.type)
            {
            case lexer::EqualEqual:
                return false;

            case lexer::ExclamationMarkEqual:
                return true;

            default:
                throw unsupported_operator(token.literal, type_of(left), type_of(right));
            }
        },
        [&token](std::monostate left, std::monostate right) -> bool
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

    result = std::visit(compare_override, left, right);
}

void interpreter::interpreter::
    visit(const parser::call_expression *call)
{
    any expr(this->evaluate(call->parameter.get()));

    const lexer::token &id = call->identifier;
    switch (id.type)
    {
    case lexer::TypeOf:
        result = type_of(expr);
        break;

    case lexer::Output:
        print(expr);
        result = std::monostate();
        break;

    case lexer::BoolCast:
        result = bool_of(expr);
        break;

    case lexer::IntCast:
        result = int_of(expr);
        break;

    case lexer::DoubleCast:
        result = double_of(expr);
        break;

    case lexer::StringCast:
        result = string_of(expr);
        break;

    default:
        throw runtime_crash("unknown call");
    }
}

void interpreter::interpreter::
    visit(const parser::assign_expression *assignment)
{
    std::string id(assignment->identifier.literal);
    any value(this->evaluate(assignment->right.get()));

    runtime_environment.set_variable(current_scope, id, value);
    result = value;
}

void interpreter::interpreter::
    interpret(parser::expression *expr)
{
    this->evaluate(expr);
}

interpreter::any interpreter::interpreter::
    get_result() const
{
    return this->result;
}