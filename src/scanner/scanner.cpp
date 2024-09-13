#include "scanner.hpp"

using namespace scanner::error;

void scanner::run(const std::string &source_code, short print_flags = 0x00)
{
    try
    {
        auto start = std::chrono::high_resolution_clock::now();

        // convert source code into tokens
        std::vector<lexer::token> tokens = std::vector<lexer::token>();
        lexer::tokenize(tokens, source_code);

        // convert tokens to abstact syntax tree
        parser::syntax_tree tree(tokens);
        tree.parse();

        // interpret ast
        interpreter::interpreter interpreter("__global");
        interpreter::any result(interpreter.interpret(tree.get_tree_root()));

        if (print_flags & scanner::flag::PRINT_DEBUG)
        {
            std::print_debug_message("source", source_code);
            std::print_debug_message("lexer", lexer::to_string(tokens));
            std::print_debug_message("parser", tree.to_ast());
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::print_debug_message("profiler", std::to_string(duration.count()) + " " + (char)230 + "s");
        }

        if (print_flags & scanner::flag::PRINT_RESPONSE)
        {
            // print result
            std::string response(std::visit(parser::variant_mapper{}, result));
            std::cout << "> " << response << "\n";
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << "\n";
    }
}

/*
REBL
 */
void scanner::run_prompt()
{
    while (true)
    {
        std::cout << "> ";

        std::string source_code;
        std::getline(std::cin, source_code);

        if (source_code.empty())
        {
            break;
        }
        scanner::run(source_code, scanner::flag::PRINT_RESPONSE);
    }
}

void scanner::run_file(const std::string &path)
{
    std::vector<std::string> source_code{};

    // read file
    std::ifstream script(path);
    if (!script.good())
    {
        throw file_not_found(path);
    }

    // load source code into memory
    std::string line;
    while (std::getline(script, line))
    {
        if (line.empty())
        {
            continue;
        }
        source_code.push_back(line);
    }

    // TODO for now execute line by line
    for (auto &&source_line : source_code)
    {
        scanner::run(source_line);
    }
}