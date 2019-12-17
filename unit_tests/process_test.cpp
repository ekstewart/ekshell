#ifndef PROCESS_TEST_CPP
#define PROCESS_TEST_CPP

#include "gtest/gtest.h"
#include "../src/process.cpp"
#include "../src/CCC.cpp"

TEST(ProcessTest, First3Connect) {
    Process p;
    CCC* first = new Connect("&&");
    CCC* second = new Connect("||");
    CCC* third = new Connect(";");
    CCC* a = new Control("a");
    CCC* b = new Control("b");
    CCC* c = new Control("c");
    CCC* d = new Control("d");
    first->addleft(a);
    first->addright(b);
    second->addleft(first);
    second->addright(c);
    third->addleft(second);
    third->addright(d);
    p.addTree(third);
    EXPECT_EQ(p.next(true), "a");
    EXPECT_EQ(p.next(true), "b");
    EXPECT_EQ(p.next(true), "d");
}

TEST(ProcessTest, quotes) {
    Process p;
    CCC* test = new Control("echo \"Hey listen!\"");
    p.addTree(test);
    EXPECT_EQ(p.next(true), "echo \"Hey listen!\"");
}

TEST(ProcessTest, exit) {
    Process p;
    CCC* test = new Control("exit");
    p.addTree(test);
    EXPECT_EQ(p.next(true), "exit");
}

TEST(ProcessTest, testCommand) {
    Process p;
    CCC* test = new Control("[test -e project/hey.txt]");
    p.addTree(test);
    EXPECT_EQ(p.next(true), "[test -e project/hey.txt]");
}

TEST(ProcessTest, endOfInput) {
    Process p;
    CCC* test = new Control("a");
    p.addTree(test);
    EXPECT_EQ(p.next(true), "a");
    EXPECT_EQ(p.next(true), "");
}

TEST(ProcessTest, semiColon) {
    Process p;
    CCC* test = new Connect("&&");
    CCC* colon = new Connect(";");
    CCC* a = new Control("a");
    CCC* b = new Control("b");
    CCC* c = new Control("c");
    colon->addleft(a);
    colon->addright(b);
    test->addleft(colon);
    test->addright(c);
    p.addTree(test);
    EXPECT_EQ(p.next(false), "a");
    EXPECT_EQ(p.next(false), "b");
    EXPECT_EQ(p.next(true), "c");
}
/*
TEST(ProcessTest, subTree) {
    Process p;
    CCC* left = new Connect(";");
    CCC* right = new Connect("&&");
    CCC* top = new Connect(";");
    CCC* a = new Control("a");
    CCC* b = new Control("b");
    CCC* c = new Control("c");
    CCC* d = new Control("d");
    left->addleft(a);
    left->addright(b);
    right->addleft(c);
    right->addright(d);
    top->addleft(left);
    top->addright(right);
    p.addTree(top);
    EXPECT_EQ(p.next(true), "a");
    EXPECT_EQ(p.next(false), "b");
    EXPECT_EQ(p.next(true), "c");
    EXPECT_EQ(p.next(false), "d");
}*/
#endif
