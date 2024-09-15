#include <argparse.hpp>

#include <iostream>

using namespace parser;

argument::argument(std::string command,
                   arg_type type,
                   arg_count count,
                   std::string help)
    : command(command),
      type(type),
      count(count),
      help(help)
{
}

argparse::
    argparse(std::string description, std::vector<argument> parse_args)
    : description(description),
      parse_args(parse_args)
{
}

argparse::
    ~argparse()
{
}

void argparse::
    set_raw_args(int argc, char *argv[])
{
    // first arg is exe
    for (size_t i = 1; i < argc; i++)
    {
        raw_args.push_back(std::string(argv[i]));
    }
}

void argparse::
    set_raw_args(std::vector<std::string> raw_args)
{
    raw_args = raw_args;
}

const argument *argparse::
    find_argument(const std::vector<std::string>::iterator &iter) const
{
    const parser::argument *arg_found;
    for (const parser::argument &argument : parse_args)
    {
        if (argument.command == *iter)
        {
            if (result_args.find(argument.command) != result_args.end())
            {
                // throw std::exception("already found command " + argument.command);
                throw std::exception();
            }
            arg_found = &argument;
            break;
        }
    }

    return arg_found;
}

void argparse::
    set_command(std::vector<std::string>::iterator &iter)
{
    std::vector<parser::arg_t> command_values{};

    const parser::argument *arg_found(this->find_argument(iter));

    // leading or trailing
    if (!arg_found)
    {
        return;
    }

    result_args[arg_found->command] = std::vector<parser::arg_t>{};

    switch (arg_found->count)
    {
    case parser::arg_count::None:
        ++iter;
        break;
    case parser::arg_count::One:
        if (!this->find_argument(++iter))
        {
            result_args[arg_found->command].push_back(*iter);
            ++iter;
        }
        break;
    case parser::arg_count::N:
        break;
    }
}

void argparse::
    add(argument argument)
{
    this->parse_args.push_back(argument);
}

void argparse::
    parse(int argc, char *argv[])
{
    this->set_raw_args(argc, argv);

    std::vector<std::string>::iterator iter = raw_args.begin();
    while (iter != raw_args.end())
    {
        this->set_command(iter);
    }
}

void argparse::
    parse(std::vector<std::string> parser_args)
{
    this->set_raw_args(parser_args);
}

parser::arg_map argparse::
    get_args()
{
    return this->result_args;
}