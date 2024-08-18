#pragma once

#include "variant.hpp"

namespace parser
{
    struct integer : public variant
    {
        integer(int value);
        ~integer();

        parser::any accept(const interpreter::visitor *visitor) const;
        std::string to_string() const;
    };
} // namespace parser
