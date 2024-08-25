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

parser::unique_expr parser::syntax_tree::
    get_numeric()
{
    lexer::token exponent_token(this->previouse());

    // float
    if (this->match({lexer::Period}))
    {
        std::string significant("0");

        if (this->match({lexer::Number}))
        {
            lexer::token mantissa_token(this->previouse());
            significant = mantissa_token.literal;
        }

        double value = std::stod(exponent_token.literal + "." + significant);

        return std::make_unique<parser::variant>(value);
    }

    int exponent = std::stoi(exponent_token.literal);
    return std::make_unique<parser::variant>(exponent);
}

parser::unique_expr parser::syntax_tree::
    get_primary()
{
    if (this->match({
            lexer::Number,
        }))
    {
        return this->get_numeric();
    }
    if (this->match({
            lexer::False,
            lexer::True,
        }))
    {
        switch (this->previouse().type)
        {
        case lexer::True:
            return std::make_unique<parser::variant>(true);
        case lexer::False:
            return std::make_unique<parser::variant>(false);
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
    get_call()
{
    if (this->match({lexer::TypeOf}))
    {
        lexer::token identifier = this->previouse();
        if (this->match({lexer::OpenRoundBracket}))
        {
            parser::unique_expr expr = this->get_expression();
            this->consume(lexer::CloseRoundBracket, "");
            return std::make_unique<parser::call_expression>(identifier, std::move(expr));
        }
    }

    return this->get_equality();
}

parser::unique_expr parser::syntax_tree::
    get_expression()
{
    return this->get_call();
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