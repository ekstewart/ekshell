#ifndef CCC_TEST_CPP
#define CCC_TEST_CPP

#include "gtest/gtest.h"
#include "../src/CCC.cpp"
#include "../src/command.cpp"
using namespace std;

TEST(CommandTest, SingleCommand) {
    CCC* test = new Command("echo hello");
    EXPECT_TRUE(test->executeCmd());
}

TEST(CommandTest, MultipleCommands){
    CCC* a = new Command("echo hello");
    CCC* b = new Command("echo \" world\"");
    CCC* andCon = new And(a,b);
    CCC* c = new Command("ls -a");
    CCC* orCon = new Or(andCon,c);
    
    EXPECT_TRUE(orCon->executeCmd());
}
TEST(CommandTest, EmptyCommand){
	CCC* a = new Command("");
	
	EXPECT_FALSE(a->executeCmd());
}
#endif
