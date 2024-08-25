#include "interpreter.hpp"
#include "variant.hpp"
#include "binary_expression.hpp"
#include "equality_expression.hpp"
#include "call_expression.hpp"

interpreter::interpreter::
    interpreter()
{
    memory = std::make_unique<std::stack<int>>();
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
    parser::any left(this->evaluate(binary->left.get()));
    parser::any right(this->evaluate(binary->right.get()));

    switch (binary->binary_operator.type)
    {
    case lexer::GreaterThan:
        return left > right;

    case lexer::GreaterThanEqual:
        return left >= right;

    case lexer::LessThan:
        return left < right;

    case lexer::LessThanEqual:
        return left <= right;

    default:
        throw parser::parser_error();
    }
}

parser::any interpreter::interpreter::
    visit(const parser::equality_expression *equal) const
{
    parser::any left(this->evaluate(equal->left.get()));
    parser::any right(this->evaluate(equal->right.get()));

    const lexer::token_type &op = equal->binary_operator.type;
    switch (op)
    {
    case lexer::EqualEqual:
        return left == right;
    case lexer::ExclamationMarkEqual:
        return left != right;

    default:
        throw parser::parser_error();
    }
}

parser::any interpreter::interpreter::
    visit(const parser::call_expression *call) const
{
    parser::any right(this->evaluate(call->parameter.get()));

    const lexer::token_type &id_type = call->identifier.type;
    switch (id_type)
    {
    case lexer::TypeOf:
        return type_of(right);
    case lexer::Bool:
        return bool_of(right);
    case lexer::Int:
        return int_of(right);
    case lexer::Double:
        return double_of(right);
    case lexer::String:
        return string_of(right);
    }
    throw parser::parser_error();
}

parser::any interpreter::interpreter::
    interpret(const parser::expression *expr) const
{
    return this->evaluate(expr);
}
