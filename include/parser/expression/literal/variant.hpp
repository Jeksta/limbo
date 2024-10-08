#pragma once

#include "literal.hpp"
#include "any.hpp"

namespace parser
{
    struct variant_visitor
    {
        virtual std::string operator()(int arg) const = 0;
        virtual std::string operator()(bool arg) const = 0;
        virtual std::string operator()(double arg) const = 0;
        virtual std::string operator()(std::string arg) const = 0;
        virtual std::string operator()(std::monostate arg) const = 0;
    };

    struct variant_ast_printer
        : public variant_visitor
    {
        std::string operator()(int arg) const;
        std::string operator()(bool arg) const;
        std::string operator()(double arg) const;
        std::string operator()(std::string arg) const;
        std::string operator()(std::monostate arg) const;
    };

    struct variant_mapper
        : public variant_visitor
    {
        std::string operator()(int arg) const;
        std::string operator()(bool arg) const;
        std::string operator()(double arg) const;
        std::string operator()(std::string arg) const;
        std::string operator()(std::monostate arg) const;
    };

    struct variant
        : public literal<interpreter::any>
    {
        variant(interpreter::any value);
        ~variant();

        void accept(interpreter::expression_visitor *visitor);
        std::string to_string() const;
    };

} // namespace parser
