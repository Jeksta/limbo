#include "variant.hpp"

std::string parser::variant_ast_printer::operator()(int arg) const
{
    return std::parenthesize({"int variant", std::to_string(arg)}, " ", std::bracket::Round);
}

std::string parser::variant_ast_printer::operator()(bool arg) const
{
    return std::parenthesize({"bool variant", arg ? "true" : "false"}, " ", std::bracket::Round);
}

std::string parser::variant_ast_printer::operator()(double arg) const
{
    return std::parenthesize({"double variant", std::to_string(arg)}, " ", std::bracket::Round);
}

std::string parser::variant_ast_printer::operator()(std::string arg) const
{
    return std::parenthesize({"string variant", arg}, " ", std::bracket::Round);
}

std::string parser::variant_ast_printer::operator()(std::monostate arg) const
{
    return std::parenthesize({"null"}, " ", std::bracket::Round);
}


std::string parser::variant_mapper::operator()(int arg) const
{
    return std::to_string(arg);
}

std::string parser::variant_mapper::operator()(bool arg) const
{
    return arg ? "true" : "false";
}

std::string parser::variant_mapper::operator()(double arg) const
{
    return std::to_string(arg);
}

std::string parser::variant_mapper::operator()(std::string arg) const
{
    return arg;
}

std::string parser::variant_mapper::operator()(std::monostate arg) const
{
    return "null";
}

parser::variant::
    variant(interpreter::any value)
    : literal(value)
{
}

parser::variant::
    ~variant()
{
}

void parser::variant::
    accept(interpreter::expression_visitor *visitor)
{
    visitor->visit(this);
}

std::string parser::variant::
    to_string() const
{
    return std::visit(variant_ast_printer{}, value);
}