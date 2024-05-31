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
std::ostream& bold_mode(std::ostream& os)
{
    return os << "\e[1m";
}

std::ostream& no_bold_mode(std::ostream& os)
{
    return os << "\e[0m";
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

void Grepped_file::find_and_print_results() const noexcept
{
    using String_array = std::array<char, def_str_len>;
    using String_array_iter = String_array::iterator;
    using Regex_iter = std::regex_iterator<String_array_iter>;

    auto input = m_stream_creator(m_file_name);
    if (input->fail()) {
        m_output << "Error: " << m_file_name << ": file not found\n";
        return;
    }

    String_array buffer{};
    std::uint32_t line_no{0U};
    while (input->getline(buffer.data(), def_str_len)) {
        line_no++;
        for (auto it = Regex_iter(buffer.begin(), buffer.end(), m_pattern); it != Regex_iter{};
             ++it) {
            auto const& file_name = std::filesystem::path(m_file_name).filename().string();
            auto line_pos = it->position();
            static constexpr auto separator{':'};

            m_output << file_name << separator << line_no << separator << line_pos << separator;
            m_output << it->format("$`");
            m_output << bold_mode << it->format("$&") << no_bold_mode;
            m_output << it->format("$'") << "\n";
        }
    }
}

} // namespace grep
