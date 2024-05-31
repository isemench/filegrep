///
/// \file grepped_file.cpp
///

#include "grepped_file.hpp"

#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>

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
    while (input->getline(buffer.data(), def_str_len)) {
        for (auto it = Regex_iter(buffer.begin(), buffer.end(), m_pattern); it != Regex_iter{};
             ++it) {
            m_output << std::filesystem::path(m_file_name).filename().string() << ": " << it->str()
                     << "\n";
        }
    }
}

} // namespace grep
