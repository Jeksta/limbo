#include "scanner_error.hpp"

scanner::error::scanner_crash::
    scanner_crash() : crash("Scanner crash")
{
}

scanner::error::scanner_crash::
    scanner_crash(std::string message) : crash(message)
{
}

scanner::error::file_not_found::
    file_not_found(std::string path)
    : scanner_crash("File does not exist: " + path)
{
}