#ifndef CMD_TEST_CPP
#define CMD_TEST_CPP

#include "gtest/gtest.h"
#include "../header/CCC.h"
#include "../src/command.cpp"
#include <vector>

TEST(TestTest, ReturnFalse)
{
    string next = "[ -e jjjijiofrjfrjio ]";
    CCC* cmd = new Command(next);

    EXPECT_FALSE(cmd->executeCmd());
}

TEST(TestTest, ReturnTrue)
{
    string next = "[ -e src ]";
    CCC* cmd = new Command(next);

    EXPECT_TRUE(cmd->executeCmd());
}


#endif
