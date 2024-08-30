#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <regex>

#include "token.hpp"
#include "token_constants.hpp"
#include "lexer_error.hpp"
#include "string_utils.hpp"

namespace lexer
{
    bool is_number(const std::string &str);
    bool is_identifier(const std::string &str);
    bool is_skippable(const std::string &str);
    bool is_keyword(const std::string &str);
    bool is_string(const std::string &str);
    bool is_literal_divider(const std::string &str);

    /*
     * Converts a literal into a token_type
     * @param string literal
     * @returns corresponding `TokeType` or `token_type::Invalid`
     */
    token_type typeof_literal(const std::string &literal);

    /*
     */
    void divide_literal(std::vector<std::string> &buffer,
                        std::string literal,
                        const std::regex &regex);

    /*
     */
    void tokenize(std::vector<token> &buffer, const std::string &source_code);

    std::string to_string(const std::vector<lexer::token> &tokens);
} // namespace lexer
