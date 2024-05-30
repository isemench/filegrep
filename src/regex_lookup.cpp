///
/// \file regex_lookup.cpp
///

#include "regex_lookup.hpp"

#include <iostream>
#include <ostream>

namespace grep {

bool has_matches(std::regex const& pattern, std::string const& text)
{
    return std::regex_search(text, pattern);
}

void find_print_matches(std::string const& print_prefix, std::string const& text,
                        std::regex const& pattern, std::ostream& out)
{
    auto match_begin = std::sregex_iterator(text.begin(), text.end(), pattern);
    auto match_end = std::sregex_iterator{};

    for (auto it = match_begin; it != match_end; ++it) {
        out << print_prefix << it->str() << "\n";
    }
}

} // namespace grep
