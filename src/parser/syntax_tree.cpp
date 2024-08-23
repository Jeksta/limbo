#include "syntax_tree.hpp"

parser::syntax_tree::
    syntax_tree(const lexer::t_vec &tokens)
    : tokens(tokens)
{
}

parser::syntax_tree::
    ~syntax_tree()
{
}

bool parser::syntax_tree::
    match(const lexer::tt_vec &types)
{
    for (const lexer::token_type &expected : types)
    {
        if (this->check(expected))
        {
            this->advance();
            return true;
        }
    }

    return false;
}

bool parser::syntax_tree::
    check(const lexer::token_type &expected) const
{
    if (this->is_end())
    {
        return false;
    }

    const lexer::token token(this->peek());
    return token.type == expected;
}

bool parser::syntax_tree::
    is_end() const
{
    return current > tokens.size() - 1;
}

void parser::syntax_tree::
    synchronize()
{
    this->advance();

    while (!this->is_end())
    {
        switch (this->peek().type)
        {
        case lexer::Condition:
            return;

        default:
            this->advance();
        }
    }
}

const lexer::token &parser::syntax_tree::
    advance()
{
    if (!this->is_end())
    {
        current++;
    }
    return this->previouse();
}

const lexer::token &parser::syntax_tree::
    consume(const lexer::token_type &expected,
            std::string error_message)
{
    if (this->check(expected))
    {
        return this->advance();
    }

    throw parser::parser_error();
}

const lexer::token &parser::syntax_tree::
    previouse() const
{
    return tokens.at(current - 1);
}

const lexer::token &parser::syntax_tree::
    peek() const
{
    return tokens.at(current);
}

// parser::unique_expr parser::syntax_tree::
//     get_binary(std::function<parser::unique_expr()> get_expr,
//                const lexer::tt_vec &comperator)
// {
//     parser::unique_expr expr = get_expr();
//     while (this->match(comperator))
//     {
//         lexer::token op = this->previouse();
//         parser::unique_expr right = get_expr();
//         expr = std::make_unique<parser::binary_expression>(std::move(expr), op, std::move(right));
//     }

//     return std::move(expr);
// }

parser::unique_expr parser::syntax_tree::
    get_primary()
{
    if (this->match({
            lexer::Number,
        }))
    {
        lexer::token prev(this->previouse());
        int value = std::stoi(prev.literal);
        // parser::any v = value;
        // return std::make_unique<parser::variant>(v);
        return std::make_unique<parser::integer>(value);
    }
    if (this->match({
            lexer::False,
            lexer::True,
        }))
    {
        switch (this->previouse().type)
        {
        case lexer::True:
            return std::make_unique<parser::boolean>(true);
        case lexer::False:
            return std::make_unique<parser::boolean>(false);
        }
    }

    if (this->match({lexer::OpenRoundBracket}))
    {
        // TODO Grouping
        // expr = get_expression() neue expression erstellen
        // consume(CloseParen) wenn es kein close gibt wirf error
        // return group expression
    }

    throw parser::parser_error();
}

parser::unique_expr parser::syntax_tree::
    get_unary()
{
    lexer::tt_vec comperator({
        lexer::ExclamationMark,
        lexer::Dash,
    });
    if (this->match(comperator))
    {
        lexer::token op = this->previouse();
        parser::unique_expr right = this->get_unary();
        return std::make_unique<parser::unary_expression>(op, std::move(right));
    }

    return this->get_primary();
}

parser::unique_expr parser::syntax_tree::
    get_factor()
{
    lexer::tt_vec comperator({
        lexer::Slash,
        lexer::Star,
    });
    auto bind = std::bind(&parser::syntax_tree::get_unary, this);
    return this->get_binary(bind, comperator);
}

parser::unique_expr parser::syntax_tree::
    get_term()
{
    lexer::tt_vec comperator({
        lexer::Dash,
        lexer::Plus,
    });
    auto bind = std::bind(&parser::syntax_tree::get_factor, this);
    return this->get_binary(bind, comperator);
}

parser::unique_expr parser::syntax_tree::
    get_comparison()
{
    lexer::tt_vec comperator({
        lexer::GreaterThan,
        lexer::GreaterThanEqual,
        lexer::LessThan,
        lexer::LessThanEqual,
    });
    auto bind = std::bind(&parser::syntax_tree::get_term, this);
    return this->get_binary(bind, comperator);
}

parser::unique_expr parser::syntax_tree::
    get_equality()
{
    lexer::tt_vec comperator({
        lexer::ExclamationMarkEqual,
        lexer::EqualEqual,
    });
    auto bind = std::bind(&parser::syntax_tree::get_comparison, this);
    return this->get_binary<parser::equality_expression>(bind, comperator);
}

parser::unique_expr parser::syntax_tree::
    get_expression()
{
    return std::move(this->get_equality());
}

void parser::syntax_tree::
    parse()
{
    this->current = 0;
    try
    {
        this->expr = this->get_expression();
    }
    catch (const parser::parser_error &e)
    {
        std::cerr << e.what() << '\n';
    }
}

const parser::expression *parser::syntax_tree::
    get_tree_root()
{
    return expr.get();
}

std::string parser::syntax_tree::
    to_ast() const
{
    return this->expr->to_string();
}