#pragma once

#include "expression.hpp"

namespace parser
{
    template <typename T>
    struct literal
        : public expression
    {
        T value;

        literal(T value) : value(value) {}
        virtual ~literal() {};
    };
} // namespace parser