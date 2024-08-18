#include "lexer.hpp"

#include <exception>

bool lexer::
    is_number(const std::string &str)
{
    // TODO
    char *p;
    strtod(str.c_str(), &p);
    return *p == 0;
}

bool lexer::
    is_identifier(const std::string &str)
{
    return std::regex_match(str, identifier_regex);
}

bool lexer::
    is_skippable(const std::string &str)
{
    return str.empty() || str == "\t" || str == "\n";
}

bool lexer::
    is_keyword(const std::string &str)
{
    return lexer::keyword_token_map.find(str) != lexer::keyword_token_map.end();
}

bool lexer::
    is_literal_divider(const std::string &str)
{
    return lexer::literal_divider_map.find(str) != lexer::literal_divider_map.end();
}

/*
Converts a literal into a token_type
@param string literal
@returns token_type
*/
lexer::token_type lexer::
    typeof_literal(const std::string &literal)
{
    if (lexer::is_skippable(literal))
    {
        return lexer::token_type::Skippable;
    }

    if (lexer::is_literal_divider(literal))
    {
        return lexer::literal_divider_map.at(literal);
    }

    if (lexer::is_keyword(literal))
    {
        return lexer::keyword_token_map.at(literal);
    }

    if (lexer::is_number(literal))
    {
        return lexer::token_type::Number;
    }

    if (lexer::is_identifier(literal))
    {
        return lexer::token_type::Identifier;
    }

    return lexer::token_type::Invalid;
}

/*
 */
void lexer::
    divide_literal(std::vector<std::string> &buffer,
                   std::string literal)
{
    std::regex_iterator<std::string::iterator> rit(literal.begin(), literal.end(), literal_divider_regex);
    std::regex_iterator<std::string::iterator> rend;

    while (rit != rend)
    {
        buffer.push_back(rit->str());
        ++rit;
    }
}

/*
 */
void lexer::
    tokenize(std::vector<lexer::token> &buffer,
             const std::string &source_code)
{
    std::vector<std::string> src = std::split(source_code, " ");

    // divide strings like 4==4
    std::vector<std::string> literals = std::vector<std::string>();
    for (const std::string &src_token : src)
    {
        lexer::divide_literal(literals, src_token);
    }

    // process literals
    for (const std::string &literal : literals)
    {
        lexer::token_type type = lexer::typeof_literal(literal);

        if (type == lexer::token_type::Invalid)
        {
            // TODO for now, do nothing
        }

        lexer::token token = lexer::token(type, literal, -1);
        buffer.push_back(token);
    }
}

std::string lexer::
    to_string(const std::vector<lexer::token> &tokens)
{
    std::string result("");
    for (const lexer::token &token : tokens)
    {
        result += std::string(token) + " ";
    }

    return result;
}