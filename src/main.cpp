#include <iostream>
#include "scanner.hpp"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        scanner::run_prompt();
    }
}