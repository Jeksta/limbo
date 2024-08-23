#include "interpreter.hpp"
#include "integer.hpp"
#include "boolean.hpp"
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

bool interpreter::interpreter::
    is_truthy(parser::any value)
{
    return std::visit(overload{
                          [](bool value) -> bool
                          {
                              return value;
                          },
                          [](int value) -> bool
                          {
                              return value == 0 ? false : true;
                          },
                      },
                      value);
}

parser::any interpreter::interpreter::
    evaluate(const parser::expression *expr) const
{
    return expr->accept(this);
}

parser::any interpreter::interpreter::
    visit(const parser::integer *integer) const
{
    return integer->value;
}

parser::any interpreter::interpreter::
    visit(const parser::boolean *boolean) const
{
    return boolean->value;
}

parser::any interpreter::interpreter::
    visit(const parser::binary_expression *binary) const
{
    parser::any left(this->evaluate(binary->left.get()));
    parser::any right(this->evaluate(binary->right.get()));

    switch (binary->binary_operator.type)
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
    visit(const parser::equality_expression *equal) const
{
    parser::any left(this->evaluate(equal->left.get()));
    parser::any right(this->evaluate(equal->right.get()));

    return std::visit(overload{
                   [equal](bool left, bool right)
                   {
                       equality<bool> eq(left, right);
                       return eq.resolve(equal->binary_operator.type);
                   },
                   [equal](int left, bool right)
                   {
                       equality<bool> eq(
                           interpreter::interpreter::is_truthy(left),
                           right);
                       return eq.resolve(equal->binary_operator.type);
                   },
                   [equal](bool left, int right)
                   {
                       equality<bool> eq(
                           left,
                           interpreter::interpreter::is_truthy(right));
                       return eq.resolve(equal->binary_operator.type);
                   },
                   [equal](int left, int right)
                   {
                       equality<int> eq(left, right);
                       return eq.resolve(equal->binary_operator.type);
                   },
               },
               left, right);

}

parser::any interpreter::interpreter::
    interpret(const parser::expression *expr) const
{
    return this->evaluate(expr);
}
