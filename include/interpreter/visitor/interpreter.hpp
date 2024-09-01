#pragma once

// forward declare
namespace parser
{
    class expression;

    class unary_expression;
    class binary_expression;
    class compare_expression;
    class arithmetic_expression;
    class call_expression;
    class assign_expression;

    class variant;
    class identifier;
}

#include <memory>
#include <stack>
#include "stdlib.hpp"
#include "expression_visitor.hpp"
#include "token.hpp"
#include "interpreter_error.hpp"
#include "runtime_environment.hpp"

namespace interpreter
{

    class interpreter
        : public expression_visitor
    {
        std::string current_scope;
        storage::runtime_environment &runtime_environment;

    private:
        any evaluate(const parser::expression *expr) const;

    public:
        interpreter(std::string scope);
        ~interpreter();

        any visit(const parser::variant *variant) const;
        any visit(const parser::identifier *identifier) const;
        
        any visit(const parser::unary_expression *unary) const;

        any visit(const parser::binary_expression *binary) const;
        any visit(const parser::compare_expression *compare) const;
        any visit(const parser::arithmetic_expression *arithmetic) const;

        any visit(const parser::call_expression *call) const;
        any visit(const parser::assign_expression *assign) const;

        any interpret(const parser::expression *expr) const;
    };

} // namespace interpreter
