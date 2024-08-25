#include "any.hpp"

std::string parser::
    type_of(const parser::any &value)
{
    return std::visit(parser::overload{
                          [](bool value)
                          {
                              return "bool";
                          },
                          [](int value)
                          {
                              return "int";
                          },
                          [](double value)
                          {
                              return "double";
                          },
                          [](std::string value)
                          {
                              return "string";
                          },
                      },
                      value);
}

bool parser::
    is_truthy(const parser::any &value)
{
    return std::visit(parser::overload{
                          [](bool value) -> bool
                          {
                              return value;
                          },
                          [](int value) -> bool
                          {
                              return value == 0 ? false : true;
                          },
                          [](double value) -> bool
                          {
                              return value == 0.0 ? false : true;
                          },
                          [](std::string value) -> bool
                          {
                              return value.size() > 0;
                          },
                      },
                      value);
}