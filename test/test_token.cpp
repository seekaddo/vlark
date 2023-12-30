// test_parser.cpp
#include <gtest/gtest.h>
#include "token.h"

class TokenTestFixture : public ::testing::Test
{
public:
    std::size_t name_len = 0;
};

TEST_F(TokenTestFixture, TokenGetNameLTest)
{
    // Test the parseInteger function
    name_len = vlark::get_name_len("abs_23_d wok");
    ASSERT_EQ(name_len, 8);
}

TEST_F(TokenTestFixture, TokenGetNameLNQeTest)
{
    name_len = vlark::get_name_len("abs_23_d wok");
    ASSERT_NE(name_len, 0);
}

TEST_F(TokenTestFixture, TokenEmptyLineEQTest)
{
    bool status = vlark::is_empty_line("      \n");
    status |= vlark::is_empty_line("     \n");
    ASSERT_TRUE(status);
}
