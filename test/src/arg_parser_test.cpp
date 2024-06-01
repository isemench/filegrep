///
/// \file arg_parser_test.cpp
///

#include "arg_parser.hpp"

#include <gtest/gtest.h>

#include <string_view>

using namespace grep;

constexpr const char* const const_args[] = {"filegrep", "some_pattern", "dir", "extra_arg"};

class Arg_parser_test : public testing::Test {
public:
    void SetUp() override
    {
        m_args = new char*[4];
        for (auto i = 0U; i < max_num_args; ++i) {
            auto size = std::string_view(const_args[i]).size();
            m_args[i] = new char[size + 1];
            std::copy(const_args[i], const_args[i] + size, m_args[i]);
            m_args[i][size] = '\0';
        }
    }

    void TearDown() override
    {
        for (auto i = 0U; i < max_num_args; ++i) {
            delete[] m_args[i];
        }
        delete[] m_args;
    }

protected:
    char** m_args;

    static constexpr auto max_num_args = 4U;

    static constexpr auto too_few_num_args = 2U;
    static constexpr auto correct_num_args = 3U;
    static constexpr auto too_much_num_args = 4U;
};

TEST_F(Arg_parser_test, Too_few_args)
{
    ASSERT_THROW(parse_args(too_few_num_args, m_args), std::invalid_argument);
}

TEST_F(Arg_parser_test, Too_much_args)
{
    ASSERT_THROW(parse_args(too_much_num_args, m_args), std::invalid_argument);
}

TEST_F(Arg_parser_test, Correct_args)
{
    auto result = parse_args(correct_num_args, m_args);
    ASSERT_EQ(result.pattern, std::string_view(const_args[1]));
    ASSERT_EQ(result.dir, std::string_view(const_args[2]));
}
