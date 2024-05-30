///
/// \file regex_lookup.hpp
///

#ifndef REGEX_LOOKUP_HPP
#define REGEX_LOOKUP_HPP

#include <iosfwd>
#include <regex>
#include <string>

namespace grep {

bool has_matches(std::regex const& pattern, std::string const& text);

void find_print_matches(std::string const& print_prefix, std::string const& text,
                        std::regex const& pattern, std::ostream& out);

} // namespace grep

#endif // REGEX_LOOKUP_HPP
