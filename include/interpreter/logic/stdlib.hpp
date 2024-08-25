#pragma once

#include "any.hpp"
#include "boollib.hpp"

namespace interpreter
{
    std::string type_of(const parser::any &value);

    bool bool_of(const parser::any &value);
    int int_of(const parser::any &value);
    double double_of(const parser::any &value);
    std::string string_of(const parser::any &value);
} // namespace interpreter
