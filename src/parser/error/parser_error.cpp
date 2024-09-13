#include "parser_error.hpp"

parser::error::parser_crash::
    parser_crash() : crash("Parser crash")
{
}

parser::error::parser_crash::
    parser_crash(std::string message) : crash(message)
{
}