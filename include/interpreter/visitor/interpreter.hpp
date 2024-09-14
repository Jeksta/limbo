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
        any result;
        storage::runtime_environment &runtime_environment;

    private:
        any evaluate(parser::expression *expr);

    public:
        interpreter(std::string scope);
        ~interpreter();

        void visit(const parser::variant *variant);
        void visit(const parser::identifier *identifier);
        void visit(const parser::unary_expression *unary);
        void visit(const parser::binary_expression *binary);
        void visit(const parser::compare_expression *compare);
        void visit(const parser::arithmetic_expression *arithmetic);
        void visit(const parser::call_expression *call);
        void visit(const parser::assign_expression *assign);

        void interpret(parser::expression *expr);

        any get_result() const;
    };

} // namespace interpreter
