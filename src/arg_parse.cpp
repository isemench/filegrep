///
/// \file arg_parse.cpp
///

#include "arg_parse.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

namespace {

constexpr int ARG_NUM = 3;

constexpr auto USAGE_STR = "Usage:\tfilegrep pattern dir_path\nWhen special characters are used, "
                           "the pattern should be placed into the single quotes\n";

constexpr auto WRONG_ARGS_STR = "Incorrect parameters provided";

} // namespace

namespace grep {

Args parse_args(int const argc, char* const argv[])
{
    if (argc != ARG_NUM) {
        throw std::invalid_argument(WRONG_ARGS_STR);
    }

    std::vector<std::string_view> const arg_list{argv + 1, argv + argc};
    return Args{arg_list[0], arg_list[1]};
}

void usage() noexcept
{
    std::cout << USAGE_STR;
}

} // namespace grep
