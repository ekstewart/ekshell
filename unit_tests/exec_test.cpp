#ifndef EXEC_TEST_CPP
#define EXEC_TEST_CPP

#include "gtest/gtest.h"
#include "../header/CCC.h"
#include "../src/command.cpp"
#include <vector>

TEST(ParseTest, ParseTestSingleToken)
{
    string testStr, str1 = "ls";
    Command* cmd = new Command(str1);
    vector<string> vec = cmd->getParsedCmdList();

    EXPECT_EQ("ls", vec.at(0));
}

TEST(ParseTest, ParseTestManyTokens)
{
    string str1 = "ls -a -l";
    Command* cmd = new Command(str1);
    vector<string> vec = cmd->getParsedCmdList();

    EXPECT_EQ("ls", vec.at(0));
    EXPECT_EQ("-a", vec.at(1));
    EXPECT_EQ("-l", vec.at(2));
}
TEST(ParseTest, ParseTestStringTokens)
{
    string str1 = "echo \"hello world\" \"oh && yeah\"";
    Command* cmd = new Command(str1);
    vector<string> vec = cmd->getParsedCmdList();

    EXPECT_EQ(vec.at(0), "echo");
    EXPECT_EQ(vec.at(1), "hello world");
    EXPECT_EQ(vec.at(2), "oh && yeah");
}
TEST(ExecTest, TestSingleTokenExec)
{
    string str1 = "ls";
    Command* cmd = new Command(str1);

    EXPECT_TRUE(cmd->executeCmd());
}
TEST(ExecTest, TestManyTokenExec)
{
    string str1 = "ls -a -l";
    Command* cmd = new Command(str1);

    EXPECT_TRUE(cmd->executeCmd());
}
TEST(ExecTest, TestSingleTokenExecFalse)
{
    string str1 = "uyguguygkyuu";
    Command* cmd = new Command(str1);

    EXPECT_FALSE(cmd->executeCmd());
}
TEST(ExecTest, TestFileTestCommand)
{
    string str1 = "[ -f names.txt ]";

    Command* cmd = new Command(str1);

    EXPECT_TRUE(cmd->executeCmd());
}
TEST(ExecTest, TestDirectoryTestCommand)
{
    string str1 = "[ -d src ]";

    Command* cmd = new Command(str1);

    EXPECT_TRUE(cmd->executeCmd());
}

TEST(ExecTest, TestExistsNoBracketsTestCommand)
{
    string str1 = "test -e CMakeLists.txt";

    Command* cmd = new Command(str1);

    EXPECT_TRUE(cmd->executeCmd());
}

TEST(ExecTest, TestBadTestCommand)
{
    string str1 = "[ -f names.txt";

    Command* cmd = new Command(str1);

    EXPECT_FALSE(cmd->executeCmd());
}
TEST(ExecTest, TestExitCommand)
{
    string str1 = "exit";

    Command* cmd = new Command(str1);
    //cmd->executeCmd();
    //uncomment above to test exit command, which will exit from test function
}



#endif
