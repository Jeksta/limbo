#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

#include "scanner_error.hpp"
#include "lexer.hpp"
#include "syntax_tree.hpp"
#include "io_stream.hpp"

namespace scanner
{
    namespace flag
    {
        const short PRINT_DEBUG = 0x01;
        const short PRINT_RESPONSE = 0x02;
    } // namespace flag

    /**
     * @brief Runs a line of code
     *
     * @param source_code
     */
    void run(const std::string &source_code, short print_flags = 0x00);

    /**
     * @brief REBL
     *
     * @return
     */
    void run_prompt(short print_flags = 0x00);

    /**
     * @brief Runs a file
     *
     * @param path
     */
    void run_file(const std::string &path);

} // namespace scanner
