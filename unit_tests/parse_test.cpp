#ifndef PARSE_TEST_CPP
#define PARSE_TEST_CPP

#include "gtest/gtest.h"
#include "../src/base.cpp"
#include "../src/parser.cpp"
#include <vector>

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
