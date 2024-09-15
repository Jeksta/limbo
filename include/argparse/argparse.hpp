#include <vector>
#include <string>
#include <variant>
#include <unordered_map>
#include <exception>

namespace parser
{
    typedef std::variant<bool, int, double, std::string> arg_t;
    typedef std::unordered_map<std::string, std::vector<arg_t>> arg_map;

    enum arg_type
    {
        Bool,
        Int,
        Double,
        String,
    };

    enum arg_count
    {
        None,
        One,
        N
    };

    struct argument
    {
        std::string command;
        arg_type type;
        arg_count count;
        std::string help;

        argument(std::string command,
                 arg_type type,
                 arg_count count,
                 std::string help);
    };

    class argparse
    {
        std::string description;
        std::vector<argument> parse_args;

        std::vector<std::string> raw_args{};
        arg_map result_args{};

    private:
        void set_raw_args(int argc, char *argv[]); 
        void set_raw_args(std::vector<std::string> raw_args);

        void set_command(std::vector<std::string>::iterator &iter);

        const argument *find_argument(const std::vector<std::string>::iterator &iter) const;
    public:
        argparse(std::string description, std::vector<argument> parse_args);
        ~argparse();

        void add(argument argument);
        void parse(int argc, char *argv[]);
        void parse(std::vector<std::string> raw_args);
        void help();

        arg_map get_args();

        friend std::ostream &operator<<(std::ostream &stream, const argparse &argparse)
        {
            return stream << argparse.description;
        }
    };

} // namespace name
