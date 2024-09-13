#include <iostream>
#include "scanner.hpp"

int main(int argc, char *argv[])
{
    switch (argc)
    {
    case 1:
        scanner::run_prompt();
        break;
    case 2:
        scanner::run_file(argv[1]);

    default:
        break;
    }
}