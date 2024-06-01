///
/// \file file_finder_test.cpp
///

#include "file_finder.hpp"

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <iostream>

using namespace grep;

constexpr auto existing_dir_path = "data";
constexpr auto non_existing_dir_path = "non_existing";
constexpr auto temporary_dir = "data/temp_dir";
constexpr auto temporary_file = "data/temp_dir/temp_file.txt";
constexpr auto temporary_text = "The quick brown fox";

constexpr File_list::size_type total_file_count = 5;

class File_finder_test : public testing::Test {
public:
    void SetUp() override
    {
        using namespace std::filesystem;

        auto test_path = path(temporary_dir);
        if (!create_directory(test_path)) {
            FAIL() << "Cannot create directory " << temporary_dir;
        }
        m_temp_dir_perms = status(temporary_dir).permissions();
    }

    void TearDown() override
    {
        using namespace std::filesystem;

        auto test_path = path(temporary_dir);
        permissions(test_path, m_temp_dir_perms, perm_options::replace);
        remove_all(test_path);
    }

    void create_temp_file()
    {
        std::ofstream os{temporary_file};
        os << temporary_text;
    }

private:
    std::filesystem::perms m_temp_dir_perms{};
};

TEST_F(File_finder_test, Find_files_in_existing_dir)
{
    auto const result = find_files(existing_dir_path);
    ASSERT_TRUE(result.error.empty()) << result.error;
    ASSERT_EQ(total_file_count, result.files.size());
}

TEST_F(File_finder_test, Find_files_in_non_existing_dir)
{
    auto const result = find_files(non_existing_dir_path);
    ASSERT_FALSE(result.error.empty());
    ASSERT_TRUE(result.files.empty());
}

TEST_F(File_finder_test, Find_files_when_permission_denied)
{
    using namespace std::filesystem;

    create_temp_file();

    auto test_path = path(temporary_dir);
    permissions(test_path, perms::none, perm_options::replace);

    auto const result = find_files(temporary_dir);
    ASSERT_TRUE(result.error.empty()) << result.error;
    ASSERT_TRUE(result.files.empty());
}

TEST_F(File_finder_test, Find_files_when_dir_is_empty)
{
    auto const result = find_files(temporary_dir);
    ASSERT_TRUE(result.error.empty()) << result.error;
    ASSERT_TRUE(result.files.empty());
}
