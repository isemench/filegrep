///
/// \file grepped_file.hpp
///

#ifndef GREPPED_FILE_HPP
#define GREPPED_FILE_HPP

#include <cstdint>
#include <iosfwd>
#include <memory>
#include <regex>
#include <string>

namespace grep {

using File_istream_creator = std::unique_ptr<std::istream> (*)(std::string const&);

class Grepped_file {
    std::string const m_file_name;
    std::regex const& m_pattern;
    File_istream_creator m_stream_creator;

    static constexpr std::uint16_t def_str_len = 512U;

public:
    Grepped_file(std::string fname, std::regex const& regex, File_istream_creator creator) noexcept;

    std::string find_and_print_results() const noexcept;
};

} // namespace grep

#endif // GREPPED_FILE_HPP
