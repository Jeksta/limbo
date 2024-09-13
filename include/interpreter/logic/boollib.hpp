#pragma once

#include "any.hpp"

namespace interpreter
{
    bool is_truthy(const interpreter::any &value);

    template <typename... T>
    bool greater_than(T... args)
    {
        return (... > args);
    }
} // namespace interpreter
