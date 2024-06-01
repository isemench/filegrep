#include "grepped_file.hpp"

#include <gtest/gtest.h>

constexpr auto regex_all_numbers = "[0-9]+";
constexpr auto regex_low_half_numbers = "[0-5]+";

constexpr auto test_file = "story.txt";
constexpr auto test_file_path = "/data/story.txt";

constexpr auto test_string =
    "The quick brown fox jumps over the lazy dog.\nAnd it jumps over it again and again, 96 times.";

constexpr auto regex_word_over = "over";
constexpr auto expected_match_word_over =
    "story.txt:1:27:The quick brown fox jumps \x1B[32mover\x1B[39m the lazy "
    "dog.\nstory.txt:2:14:And it jumps \x1B[32mover\x1B[39m it again and again, 96 times.\n";

constexpr auto expected_match_numbers =
    "story.txt:2:39:And it jumps over it again and again, \x1B[32m96\x1B[39m times.\n";

class Grepped_file_test : public testing::Test {
protected:
    grep::File_istream_creator creator = [](std::string const&) -> std::unique_ptr<std::istream> {
        return std::make_unique<std::istringstream>(test_string);
    };
};

TEST_F(Grepped_file_test, Match_a_word)
{
    std::regex pattern{regex_word_over};

    grep::Grepped_file grepped{test_file, pattern, creator};
    std::ostringstream actual{};
    actual << grepped.find_and_print_results();
    EXPECT_EQ(expected_match_word_over, actual.str());
}

TEST_F(Grepped_file_test, Match_a_number)
{
    std::regex pattern{regex_all_numbers};

    grep::Grepped_file grepped{test_file, pattern, creator};
    std::ostringstream actual{};
    actual << grepped.find_and_print_results();
    EXPECT_EQ(expected_match_numbers, actual.str());
}

TEST_F(Grepped_file_test, Dont_match_anything)
{
    std::regex pattern{regex_low_half_numbers};

    grep::Grepped_file grepped{test_file, pattern, creator};
    std::ostringstream actual{};
    actual << grepped.find_and_print_results();
    EXPECT_TRUE(actual.str().empty());
}
