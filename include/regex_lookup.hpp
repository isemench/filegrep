///
/// \file regex_lookup.hpp
///

#ifndef REGEX_LOOKUP_HPP
#define REGEX_LOOKUP_HPP

#include <regex>
#include <string>

namespace grep {

bool find_matches(std::regex const& pattern, std::string text);

} // namespace grep

#endif // REGEX_LOOKUP_HPP
