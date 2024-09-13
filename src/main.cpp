#include "scanner.hpp"

int main(int argc, char *argv[])
{
    switch (argc)
    {
    case 1:
        scanner::run_prompt();
        break;
    case 2:
        // TODO argparser
        if (std::string(argv[1]) == "-d")
        {
            scanner::run_prompt(scanner::flag::PRINT_DEBUG);
        }
        else
        {
            scanner::run_file(argv[1]);
        }
        break;

    default:
        break;
    }
}