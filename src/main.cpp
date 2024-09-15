#include "scanner.hpp"
#include "argparse.hpp"

int main(int argc, char *argv[])
{
    parser::argparse arg_parser(
        "Test",
        {
            {"-d", parser::arg_type::Bool, parser::arg_count::None, "print debug messages after every instruction"},
            {"-help", parser::arg_type::Bool, parser::arg_count::None, "print debug messages after every instruction"},
        });

    arg_parser.parse(argc, argv);
    auto args = arg_parser.get_args();

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