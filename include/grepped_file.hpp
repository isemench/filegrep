///
/// \file grepped_file.hpp
///

#ifndef GREPPED_FILE_HPP
#define GREPPED_FILE_HPP

#include <cstdint>
#include <iosfwd>
#include <regex>
#include <string>

namespace grep {

class Grepped_file {
    std::string const m_file_name;
    std::regex const& m_pattern;
    std::ostream& m_output;

    static constexpr std::uint16_t def_str_len = 512U;

public:
    Grepped_file(std::string fname, std::regex const& regex, std::ostream& out) noexcept;

    void find_and_print_results() const noexcept;
};

} // namespace grep

#endif // GREPPED_FILE_HPP
