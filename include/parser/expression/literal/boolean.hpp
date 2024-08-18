#pragma once

#include "variant.hpp"

namespace parser
{
    struct boolean : public variant
    {
        boolean(bool value);
        ~boolean();

        parser::any accept(const interpreter::visitor *visitor) const;
        std::string to_string() const;
    };
} // namespace parser
