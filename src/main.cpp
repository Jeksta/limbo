#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <memory>
#include <variant>

#include "scanner.hpp"
#include "syntax_tree.hpp"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        scanner::run_prompt();
    }
}