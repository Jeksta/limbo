#include "lexer_error.hpp"

lexer::error::invalid_token::
    invalid_token(const lexer::token &token) : crash("Invalid token: " + token.literal)
{
}