#ifndef EXEC_TEST_CPP
#define EXEC_TEST_CPP

#include "gtest/gtest.h"
#include "../src/base.cpp"
#include "../src/parser.cpp"
#include <vector>

TEST(CommandParseTest, ParseTestSingleToken)
{
    string testStr, str1 = "ls";
    Command* cmd = new Command(str1);
    vector<string> vec = cmd->getParsedCmdList();

    EXPECT_EQ("ls", vec.at(0));
}

TEST(CommandParseTest, ParseTestManyTokens)
{
    string str1 = "ls -a -l";
    Command* cmd = new Command(str1);
    vector<string> vec = cmd->getParsedCmdList();

    EXPECT_EQ("ls", vec.at(0));
    EXPECT_EQ("-a", vec.at(1));
    EXPECT_EQ("-l", vec.at(2));
}
TEST(CommandParseTest, ParseTestStringTokens)
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
TEST(TestTest, TestFileTestCommand)
{
    string str1 = "[ -f README.md ]";

    Command* cmd = new Command(str1);

    EXPECT_TRUE(cmd->executeCmd());
}
TEST(TestTest, TestDirectoryTestCommand)
{
    string str1 = "[ -d src ]";

    Command* cmd = new Command(str1);

    EXPECT_TRUE(cmd->executeCmd());
}

TEST(TestTest, TestExistsNoBracketsTestCommand)
{
    string str1 = "test -e CMakeLists.txt";

    Command* cmd = new Command(str1);

    EXPECT_TRUE(cmd->executeCmd());
}

TEST(TestTest, TestBadTestCommand)
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
TEST(TestTest, ReturnFalse)
{
    string next = "[ -e jjjijiofrjfrjio ]";
    Base* cmd = new Command(next);
    
    EXPECT_FALSE(cmd->executeCmd());
}

TEST(TestTest, ReturnTrue)
{
    string next = "[ -e src ]";
    Base* cmd = new Command(next);
    
    EXPECT_TRUE(cmd->executeCmd());
}
TEST(InputParse, ParseSingleCommand){
    string str = "echo h";
    Parser p;
    vector<string> vec = p.getTokens(str);
    EXPECT_EQ(vec.at(0),"echo h");
}
TEST(InputParse, ParseConnectedCommands){
    string str = "ls && echo h";
    Parser p;
    vector<string> vec = p.getTokens(str);
    
    EXPECT_EQ(vec.at(0),"ls");
    EXPECT_EQ(vec.at(1),"&&");
    EXPECT_EQ(vec.at(2),"echo h");
}
TEST(InputParse, ParseParentheses){
    string str = "(jijiijijijij) && echo h";
    Parser p;
    vector<string> vec = p.getTokens(str);
    
    EXPECT_EQ(vec.at(0),"(jijiijijijij)");
    EXPECT_EQ(vec.at(1),"&&");
    EXPECT_EQ(vec.at(2),"echo h");
}
TEST(InputParse, ParseSingleRedirect){
	string str = "cat < file.txt";
	Parser p;
	vector<string> vec = p.getTokens(str);
	
	EXPECT_EQ(vec.at(0),"cat");
	EXPECT_EQ(vec.at(1),"<");
	EXPECT_EQ(vec.at(2),"file.txt");
}
TEST(InputParse, ParseMultipleRedirect){
	string str = "((echo h) >> file.txt)|less ; echo done";
	Parser p;
	vector<string> vec = p.getTokens(str);
	
	EXPECT_EQ(vec.at(0),"((echo h) >> file.txt)");
	EXPECT_EQ(vec.at(1),"|");
	EXPECT_EQ(vec.at(2),"less");
	EXPECT_EQ(vec.at(3),";");
	EXPECT_EQ(vec.at(4),"echo done");
}



#endif
