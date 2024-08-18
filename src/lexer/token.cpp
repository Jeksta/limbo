#include "token.hpp"


lexer::token::token(lexer::token_type _type, std::string _literal, int _line)
    : type(_type), literal(_literal), line(_line)
{
}

lexer::token::~token()
{
}
