#include "file_finder.hpp"
#include "grepped_file.hpp"

#include <gtest/gtest.h>

#include <filesystem>

constexpr auto regex_all_numbers = "[0-9]+";
constexpr auto regex_low_half_numbers = "[0-5]+";
constexpr auto regex_one_word = "\\w+";
constexpr auto regex_specific_word = "over";

constexpr auto test_string =
    "The quick brown fox jumps over the lazy dog.\nThis sentence is repeated 96 times.";

class Regex_lookup_test : public testing::Test {};

TEST_F(Regex_lookup_test, Test)
{
    std::regex pattern{regex_specific_word};
    grep::File_istream_creator creator = [](std::string const&) -> std::unique_ptr<std::istream> {
        return std::make_unique<std::istringstream>(test_string);
    };
    grep::Grepped_file test_file{"test_text_file.txt", pattern, std::cout, creator};
    test_file.find_and_print_results();
}

TEST_F(Regex_lookup_test, Enum_files)
{
    std::cout << "Current dir: " << std::filesystem::current_path() << "\n";
    auto files = grep::find_files(".");
    for (auto const& file : files) {
        std::cout << file << "\n";
    }
}
