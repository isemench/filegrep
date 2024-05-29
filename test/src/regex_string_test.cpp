#include "regex_lookup.hpp"

#include <gtest/gtest.h>

constexpr auto regex_numbers = "[0-9]+";

constexpr auto test_string = "The quick brown fox counts 93 rabbits";

class Regex_lookup_test : public testing::Test {};

TEST_F(Regex_lookup_test, Regex_numbers_found)
{
    std::regex pattern{regex_numbers};
    ASSERT_TRUE(grep::find_matches(pattern, test_string));
}
