///
/// \file arg_parse.cpp
///

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <vector>

namespace {

constexpr int ARG_MAX = 3;

constexpr auto usage_str = "Usage:\tfilegrep {PATTERN} dir_path\n";

constexpr auto too_many_args_str = "Too many parameters provided";

} // namespace

namespace grep {

void parse_args(int const argc, char* const argv[])
{
    if (argc > ARG_MAX) {
        throw std::invalid_argument(too_many_args_str);
    }
    std::vector<std::string_view> const args{argv + 1, argv + argc};
    for (auto const arg : args) {
        std::cout << arg << " ";
    }
    std::cout << "\n";
}

void usage()
{
    std::cout << usage_str;
}

} // namespace grep
