#pragma once

#include <unordered_map>
#include <regex>
#include "token.hpp"

namespace lexer
{
    const static std::unordered_map<std::string, token_type> keyword_token_map{
        // Keywords
        {"true", True},
        {"false", False},
        {"if", Condition},

        {"func", Function},
        {"int", Integer},
        {"return", Return},
    };

    const static std::unordered_map<std::string, token_type> literal_divider_map{
        // Brackets
        {"(", OpenRoundBracket},
        {")", CloseRoundBracket},
        {"[", OpenSquareBraket},
        {"]", CloseSquareBracket},
        {"{", OpenCurlyBraket},
        {"}", CloseCurlyBracket},

        // Symbols
        {"!", ExclamationMark},
        {"?", QuestionMark},

        {"=", Equal},
        {"!=", ExclamationMarkEqual},
        {"==", EqualEqual},
        {"=>", EqualArrow},
        {"<=", LessThanEqual},
        {">=", GreaterThanEqual},

        {"<", LessThan},
        {"<<", LessThanLessThan},

        {">", GreaterThan},
        {">>", GreaterThanGreaterThan},

        {"+", Plus},
        {"++", PlusPlus},

        {"-", Dash},
        {"--", DashDash},
        {"->", DashArrow},

        {"*", Star},
        {"**", StarStar},

        {"/", Slash},

        {"&", Ampersand},
        {"&&", AmpersandAmpersand},

        {"|", VerticalLine},
        {"||", VerticalLineVerticalLine},

        {"%", Percent},
        {":", Colon},
        {".", Period},
        {",", Comma},
    };

    constexpr std::regex_constants::syntax_option_type regex_options(std::regex_constants::optimize);
    const std::regex identifier_regex("([_a-zA-Z][_a-zA-Z0-9]{0,30})", regex_options);
    const std::regex literal_divider_regex("([!\\<\\>\\&*/\\+\\-\\|=]{1,2}|[\\(\\)\\[\\]%:]|[^!\\(\\)\\[\\]=%\\&*/\\+\\-\\|\\<\\>:]+)", regex_options);
}