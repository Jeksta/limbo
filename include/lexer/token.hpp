#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <magic_enum.hpp>
#include "string_utils.hpp"

namespace lexer
{
    enum token_type
    {
        Invalid,
        Skippable,

        // Backets
        OpenRoundBracket,
        CloseRoundBracket,
        OpenSquareBraket,
        CloseSquareBracket,
        OpenCurlyBraket,
        CloseCurlyBracket,

        // Symbols
        ExclamationMark,
        QuestionMark,

        Equal,
        EqualEqual,
        ExclamationMarkEqual,
        EqualArrow,
        GreaterThanEqual,
        LessThanEqual,

        GreaterThan,
        GreaterThanGreaterThan,

        LessThan,
        LessThanLessThan,

        Star,
        StarStar,

        Plus,
        PlusPlus,

        Dash,
        DashDash,
        DashArrow,

        Slash,

        Ampersand,
        AmpersandAmpersand,

        VerticalLine,
        VerticalLineVerticalLine,

        Percent,
        Colon,
        Period,
        Comma,

        //
        Identifier,
        Number,

        // Keywords
        True,
        False,
        Condition,
        Return,

        Function,
        TypeOf,
        Bool,
        Int,
        Double,
        String,
    };

    struct token
    {
        token_type type;
        std::string literal;
        int line;

    public:
        token(token_type _type, std::string _literal, int _line);
        ~token();

        friend std::ostream &operator<<(std::ostream &str, const token &token)
        {
            std::string enum_name(magic_enum::enum_name(token.type));

            return str << std::parenthesize({enum_name, ":", token.literal}, " ", std::bracket::Square);
        }

        operator std::string() const
        {
            std::string enum_name(magic_enum::enum_name(type));

            return std::parenthesize({enum_name, ":", literal}, " ", std::bracket::Square);
        }
    };

    typedef std::vector<token>::const_iterator t_citer;
    typedef std::vector<token_type> tt_vec;
    typedef std::vector<token> t_vec;

}