///
/// \file file_finder_test.cpp
///

#include "file_finder.hpp"

#include <gtest/gtest.h>

constexpr auto test_dir_path = "/home/user/.local";
constexpr auto test_nested_dir_path = "/home/user/.local/share";
constexpr auto test_file_1 = "/home/user/.local/share/story.txt";

using namespace grep;

TEST(File_finder_test, Find_files_in_existing_dir)
{
    ASSERT_FALSE(find_files(test_dir_path).empty());
}
