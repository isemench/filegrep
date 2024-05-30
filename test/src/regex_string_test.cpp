#include "grepped_file.hpp"
#include "regex_lookup.hpp"

#include <gtest/gtest.h>

constexpr auto regex_all_numbers = "[0-9]+";
constexpr auto regex_low_half_numbers = "[0-5]+";
constexpr auto regex_one_word = "\\w+";
constexpr auto regex_specific_word = "over";

constexpr auto test_string =
    "The quick brown fox jumps over the lazy dog. This sentence is repeated 96 times.";

class Regex_lookup_test : public testing::Test {};

TEST_F(Regex_lookup_test, Regex_numbers_found)
{
    std::regex pattern{regex_all_numbers};
    ASSERT_TRUE(grep::has_matches(pattern, test_string));
}

TEST_F(Regex_lookup_test, Regex_numbers_not_found)
{
    std::regex pattern{regex_low_half_numbers};
    ASSERT_FALSE(grep::has_matches(pattern, test_string));
}

TEST_F(Regex_lookup_test, Test)
{
    std::regex pattern{regex_specific_word};
    grep::Grepped_file test_file{"/home/igse906/Projects/filegrep/test/data/test_text_file.txt",
                                 pattern, std::cout};
    test_file.find_and_print_results();
}
