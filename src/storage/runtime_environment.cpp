#include "runtime_environment.hpp"

using namespace interpreter::error;

storage::runtime_environment::
    runtime_environment()
{
}

void storage::runtime_environment::
    set_variable(const std::string &scope_name, const std::string &identifier, interpreter::any value)
{
    scope_map[scope_name][identifier] = value;
}

interpreter::any storage::runtime_environment::
    get_variable(const std::string &scope_name, const std::string &identifier) const
{
    if (!this->is_in_scope<std::string, storage::scope>(scope_map, scope_name))
    {
        throw runtime_crash("undefined scope: " + scope_name);
    }

    if (!this->is_in_scope<std::string, interpreter::any>(scope_map.at(scope_name), identifier))
    {
        throw runtime_crash("undefined identifier: " + scope_name + "::" + identifier);
    }

    return scope_map.at(scope_name).at(identifier);
}