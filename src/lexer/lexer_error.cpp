#include "lexer_error.hpp"

const char *lexer::invalid_token::
    what() const throw()
{
    return "Invalid token";
}