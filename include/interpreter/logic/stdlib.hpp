#pragma once

#include <iostream>
#include "error.hpp"
#include "boollib.hpp"

namespace interpreter
{
    std::string type_of(const interpreter::any &value);

    bool bool_of(const interpreter::any &value);
    int int_of(const interpreter::any &value);
    double double_of(const interpreter::any &value);
    std::string string_of(const interpreter::any &value);

    void print(const interpreter::any &value);
} // namespace interpreter
