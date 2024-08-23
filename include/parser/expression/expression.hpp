#pragma once

#include <memory>
#include "error.hpp"
#include "parser_error.hpp"
#include "string_utils.hpp"

#include "token.hpp"
#include "interpreter.hpp"

namespace parser
{

    class expression
        : public interpreter::interpretable
    {
    public:
        virtual ~expression() {}

        virtual std::string to_string() const = 0;
    };

    typedef std::unique_ptr<expression> unique_expr;
    typedef std::shared_ptr<expression> shared_expr;
}