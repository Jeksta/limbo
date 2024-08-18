#include "parser_error.hpp"

const char *parser::parser_error::
    what() const throw()
{
    return "Parser error";
}