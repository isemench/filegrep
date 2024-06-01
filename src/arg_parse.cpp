///
/// \file arg_parse.cpp
///

#include "arg_parse.hpp"

#include <ostream>
#include <stdexcept>
#include <vector>

namespace {

constexpr int arg_num = 3;

constexpr auto usage_str = "Usage:\tfilegrep pattern dir_path\nWhen special characters are used, "
                           "the pattern should be placed into the single quotes\n";

constexpr auto wrong_args_str = "Incorrect parameters provided";

} // namespace

namespace grep {

Args parse_args(int const argc, char* const argv[])
{
    if (argc != arg_num) {
        throw std::invalid_argument(wrong_args_str);
    }

    std::vector<std::string_view> const arg_list{argv + 1, argv + argc};
    return Args{arg_list[0], arg_list[1]};
}

void usage(std::ostream& os) noexcept
{
    os << usage_str;
}

} // namespace grep
