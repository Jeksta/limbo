#include "interpreter_error.hpp"

interpreter::error::runtime_crash::
    runtime_crash() : crash("runtime crash")
{
}

interpreter::error::runtime_crash::
    runtime_crash(std::string message) : crash(message)
{
}

interpreter::error::unsupported_operator::
    unsupported_operator(std::string op, std::string ltype, std::string rtype)
    : runtime_crash("unsupported operator '" + op + "' for left type : right type -> '" + ltype + "' : '" + rtype + "'")
{
}

interpreter::error::arithmetic_crash::
    arithmetic_crash(std::string message)
    : runtime_crash(message)
{
}