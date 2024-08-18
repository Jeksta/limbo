#include "interpreter.hpp"
#include "integer.hpp"
#include "binary_expression.hpp"
#include "equality_expression.hpp"

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
    visit_integer(const parser::integer *integer) const
{
    return integer->value;
}

parser::any interpreter::interpreter::
    visit_binary_expression(const parser::binary_expression *expr) const
{
    parser::any left(this->evaluate(expr->left.get()));
    parser::any right(this->evaluate(expr->right.get()));

    switch (expr->binary_operator.type)
    {
    case lexer::EqualEqual:
    {
        return left == right;
    }
    break;
    case lexer::ExclamationMarkEqual:
    {
        return left != right;
    }
    break;

    default:
        throw parser::parser_error();
    }
}

parser::any interpreter::interpreter::
    visit_equality_expression(const parser::equality_expression *expr) const
{
    throw std::not_implemented();
}

parser::any interpreter::interpreter::
    interpret(const parser::expression *expr) const
{
    return this->evaluate(expr);
}
