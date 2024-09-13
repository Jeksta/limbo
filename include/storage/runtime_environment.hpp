#pragma once

#include "unordered_map"
// #include "scope.hpp"
#include "interpreter_error.hpp"
#include "any.hpp"

namespace storage
{
    typedef std::unordered_map<std::string, interpreter::any> scope;
    typedef std::unordered_map<std::string, scope> chain_map;

    class runtime_environment
    {
        chain_map scope_map{{"__global", scope{}}};

    public:
        static runtime_environment &get_instance()
        {
            static runtime_environment instance;

            return instance;
        }

    private:
        runtime_environment();

        template <typename K, typename V>
        bool is_in_scope(const std::unordered_map<K, V> &map,
                         const K &name) const
        {
            auto got_scope(map.find(name));
            return got_scope != map.end();
        }

    public:
        runtime_environment(runtime_environment &other) = delete;
        void operator=(const runtime_environment &) = delete;

        void set_variable(const std::string &scope_name,
                          const std::string &identifier,
                          interpreter::any value);
        interpreter::any get_variable(const std::string &scope_name,
                                      const std::string &identifier) const;
    };
} // namespace storage
