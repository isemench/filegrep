///
/// \file grepped_file.cpp
///

#include "grepped_file.hpp"

#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>

namespace {
std::ostream& green_color_mode(std::ostream& os)
{
    return os << "\e[32m";
}

std::ostream& def_color_mode(std::ostream& os)
{
    return os << "\e[39m";
}

std::istream& getline(std::istream& is, std::string& str, std::streamsize n,
                      char const delim = '\n')
{
    str.resize(n);
    is.getline(&str[0], n, delim);
    if (!is.fail()) {
        std::streamsize const read = std::char_traits<char>::length(&str[0]);
        str.resize(read);
    }
    return is;
}

} // namespace

namespace grep {

constexpr std::uint16_t Grepped_file::def_str_len;

Grepped_file::Grepped_file(std::string fname, std::regex const& regex, std::ostream& out,
                           File_istream_creator creator) noexcept
    : m_file_name{std::move(fname)}
    , m_pattern{regex}
    , m_output{out}
    , m_stream_creator{std::move(creator)}
{
}

std::string Grepped_file::find_and_print_results() const noexcept
{
    using Regex_iter = std::sregex_iterator;

    auto input = m_stream_creator(m_file_name);
    std::ostringstream output{};
    if (input->fail()) {
        output << "Error: " << m_file_name << ": file not found\n";
        return output.str();
    }

    std::string buffer{};
    std::uint32_t line_no{1U};
    while (getline(*input, buffer, def_str_len)) {
        for (auto it = Regex_iter(buffer.begin(), buffer.end(), m_pattern); it != Regex_iter{};
             ++it) {
            auto const& file_name = std::filesystem::path(m_file_name).filename().string();
            auto line_pos = it->position() + 1;
            static constexpr auto separator{':'};

            if (it->length() > 0) {
                output << file_name << separator << line_no << separator << line_pos << separator;
                output << it->format("$`");
                output << green_color_mode << it->format("$&") << def_color_mode;
                output << it->format("$'") << "\n";
            }
        }
        line_no++;
    }

    return output.str();
}

} // namespace grep
