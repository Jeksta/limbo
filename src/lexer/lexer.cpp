#include "lexer.hpp"

using namespace lexer::error;

bool lexer::
    is_number(const std::string &str)
{
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
    is_string(const std::string &str)
{
    if (str.length() < 2)
    {
        return false;
    }

    return std::starts_with(str, string_delimiter) &&
           std::ends_with(str, string_delimiter);
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
        return lexer::Skippable;
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
        return lexer::Number;
    }

    if (lexer::is_string(literal))
    {
        return lexer::String;
    }

    if (lexer::is_identifier(literal))
    {
        return lexer::Identifier;
    }

    return lexer::Invalid;
}

void lexer::
    divide_literal(std::vector<std::string> &buffer,
                   std::string literal,
                   const std::regex &regex)
{
    std::regex_iterator<std::string::iterator> rit(literal.begin(), literal.end(), regex);
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
    // seperate source by strings and whilespaces
    std::vector<std::string> src{};
    lexer::divide_literal(src, source_code, string_divider_regex);

    std::vector<std::string> literals{};
    for (const std::string &src_token : src)
    {
        // skip strings
        if (std::starts_with(src_token, string_delimiter))
        {
            literals.push_back(src_token);
            continue;
        }

        // divide literals like 4==4 -> {4, ==, 4}
        lexer::divide_literal(literals, src_token, literal_divider_regex);
    }

    // process literals
    for (const std::string &literal : literals)
    {
        lexer::token_type type = lexer::typeof_literal(literal);
        std::string destringed_literal(std::remove_chars(literal, string_delimiter));
        lexer::token token = lexer::token(type, destringed_literal, -1);

        if (type == lexer::token_type::Invalid)
        {
            throw invalid_token(token);
        }

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