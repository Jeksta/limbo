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

    // return std::visit(overload{
    //                       [op](bool left, bool right)
    //                       {
    //                           return equals<bool>(left, right, op);
    //                       },
    //                       [op](int left, bool right)
    //                       {
    //                           bool truthy = interpreter::interpreter::is_truthy(left);
    //                           return equals<bool>(truthy, right, op);
    //                       },
    //                       [op](bool left, int right)
    //                       {
    //                           bool truthy = interpreter::interpreter::is_truthy(right);
    //                           return equals<bool>(truthy, truthy, op);
    //                       },
    //                       [op](int left, int right)
    //                       {
    //                           return equals<int>(left, right, op);
    //                       },
    //                       [op](bool left, double right)
    //                       {
    //                           bool truthy = interpreter::interpreter::is_truthy(right);
    //                           return equals<bool>(left, truthy, op);
    //                       },
    //                       [op](double left, bool right)
    //                       {
    //                           bool truthy = interpreter::interpreter::is_truthy(left);
    //                           return equals<bool>(truthy, right, op);
    //                       },
    //                       [op](int left, double right)
    //                       {
    //                           return equals<double>(1.0 * left, right, op);
    //                       },
    //                       [op](double left, int right)
    //                       {
    //                           return equals<double>(left, 1.0 * right, op);
    //                       },
    //                       [op](double left, double right)
    //                       {
    //                           return equals<double>(left, right, op);
    //                       },
    //                   },
    //                   left, right);
}

parser::any interpreter::interpreter::
    visit(const parser::call_expression *call) const
{
    parser::any right(this->evaluate(call->parameter.get()));

    const lexer::token_type &id_type = call->identifier.type;
    switch (id_type)
    {
    case lexer::TypeOf:
        return parser::type_of(right);
    }
    throw parser::parser_error();
}

parser::any interpreter::interpreter::
    interpret(const parser::expression *expr) const
{
    return this->evaluate(expr);
}
