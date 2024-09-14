#pragma once

#include <vector>
#include <memory>
#include <functional>
#include "any.hpp"
#include "parser_error.hpp"
#include "token.hpp"
#include "variant.hpp"
#include "identifier.hpp"
#include "unary_expression.hpp"
#include "binary_expression.hpp"
#include "compare_expression.hpp"
#include "arithmetic_expression.hpp"
#include "call_expression.hpp"
#include "assign_expression.hpp"

namespace parser
{
    class syntax_tree
    {
        const lexer::t_vec tokens;
        int current = 0;

        unique_expr expr;

    private:
        bool match(const lexer::tt_vec &types);
        bool check(const lexer::token_type &expected) const;
        bool is_end() const;
        void synchronize();

        const lexer::token &advance();
        const lexer::token &consume(const lexer::token_type &expected,
                                    std::string error_message);
        const lexer::token &previouse() const;
        const lexer::token &peek() const;

        // rules
        unique_expr get_numeric();
        unique_expr get_call();
        unique_expr get_assignment();
        unique_expr get_primary();
        unique_expr get_unary();
        // binary rules
        template <typename T = binary_expression>
        unique_expr get_binary(std::function<unique_expr()> get_expr,
                               const lexer::tt_vec &comperator)
        {
            unique_expr expr = get_expr();
            while (this->match(comperator))
            {
                lexer::token op = this->previouse();
                unique_expr right = get_expr();
                expr = std::make_unique<T>(std::move(expr), op, std::move(right));
            }

            return std::move(expr);
        }
        unique_expr get_factor();
        unique_expr get_term();
        unique_expr get_comparison();
        unique_expr get_equality();

        unique_expr get_expression();

    public:
        syntax_tree(const lexer::t_vec &tokens);
        ~syntax_tree();

        void parse();

        expression *get_tree_root();

        std::string to_ast() const;
    };

} // namespace parser
