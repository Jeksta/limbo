#include "scanner.hpp"

void scanner::run(const std::string &source_code)
{
    try
    {
        std::print_debug_message("source", source_code);

        // convert source code into tokens
        std::vector<lexer::token> tokens = std::vector<lexer::token>();
        lexer::tokenize(tokens, source_code);
        std::print_debug_message("lexer", lexer::to_string(tokens));

        // convert tokens to abstact syntax tree
        parser::syntax_tree tree(tokens);
        tree.parse();
        std::print_debug_message("parser", tree.to_ast());

        interpreter::interpreter interpreter;
        parser::any result(interpreter.interpret(tree.get_tree_root()));

        std::string response(std::visit(parser::variant_mapper{}, result));
        std::cout << "> " << response << "\n";
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

        scanner::run(source_code);
    }
}

void scanner::run_file(const std::string &path)
{
    throw std::not_implemented();
}