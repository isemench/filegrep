///
/// \file arg_parse.hpp
///

#ifndef ARG_PARSE_HPP
#define ARG_PARSE_HPP

#include <iosfwd>
#include <string_view>

namespace grep {

struct Args {
    std::string_view pattern{};
    std::string_view dir{};
};

Args parse_args(int const argc, char* const argv[]);

void usage(std::ostream& os) noexcept;

} // namespace grep

#endif // ARG_PARSE_HPP
