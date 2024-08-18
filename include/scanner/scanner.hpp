#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "error.hpp"
#include "lexer.hpp"
#include "syntax_tree.hpp"
#include "io_stream.hpp"

namespace scanner
{
    /**
     * @brief Runs a line of code
     * 
     * @param source_code 
     */
    void run(const std::string &source_code);

    /**
     * @brief REBL
     * 
     * @return  
     */
    void run_prompt();

    /**
     * @brief Runs a file
     * 
     * @param path 
     */
    void run_file(const std::string &path);

} // namespace scanner
