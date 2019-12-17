#ifndef READ_TEST_CPP
#define READ_TEST_CPP

#include "gtest/gtest.h"
#include "../src/read.cpp"
#include "../src/CCC.cpp"
#include "../src/reference.cpp"
#include "../src/process.cpp"

TEST(ReadTest, Assign2ReadCreate) {
    Read test;
    EXPECT_TRUE(test.TESTINGinputTree("echo a || echo b && echo c; echo d"));
    EXPECT_TRUE(test.TESTINGinputTree("echo b#c"));
}

TEST(ReadTest, OneWord) {
    Read test;
    Process p;
    p.addTree(test.TESTINGinputTree("Heyo"));
    EXPECT_EQ(p.next(true), "Heyo");
}

TEST(ReadTest, TwoWord) {
    Read test;
    Process p;
    p.addTree(test.TESTINGinputTree("echo one"));
    EXPECT_EQ(p.next(true), "echo one");
}

TEST(ReadTest, LongString) {
    Read test;
    Process p;
    p.addTree(test.TESTINGinputTree("One Two Three Four Five Six"));
    EXPECT_EQ(p.next(true), "One Two Three Four Five Six");
}

TEST(ReadTest, Quote) {
    Read test;
    Process p;
    p.addTree(test.TESTINGinputTree("echo \"a or b\""));
    EXPECT_EQ(p.next(true), "echo \"a or b\"");
}

TEST(ReadTest, UnclosedQuote) {
    Read test;
    Process p;
    p.addTree(test.TESTINGinputTree("echo \"a or b"));
    EXPECT_EQ(p.next(true), "echo \"a or b");
}

TEST(ReadTest, Assign2Connect) {
    Read test;
    Process p;
    p.addTree(test.TESTINGinputTree("echo a || echo b && echo c; echo d"));
    EXPECT_EQ(p.next(true), "echo a");
    EXPECT_EQ(p.next(false), "echo b");
    EXPECT_EQ(p.next(true), "echo c");
    EXPECT_EQ(p.next(false), "echo d");
}

TEST(ReadTest, SecondTreeAndComment){
    Read test;
    Process p;
    test.TESTINGinputTree("first");
    p.addTree(test.TESTINGinputTree("echo b#c"));
    EXPECT_EQ(p.next(true), "echo b");
}

TEST(ReadTest, ExitAndEnd) {
    Read test;
    Process p;
    p.addTree(test.TESTINGinputTree("exit failed"));
    EXPECT_EQ(p.next(true), "exit");
    EXPECT_EQ(p.next(true), "");
}

TEST(ReadTest, EmptyString) {
    Read test;
    Process p;
    p.addTree(test.TESTINGinputTree(" "));
    EXPECT_EQ(p.next(true), "");
    p.addTree(test.TESTINGinputTree(""));
    EXPECT_EQ(p.next(true), "");
}

TEST(ReadTest, TestConnect) {
    Read test;
    Process p;
    std::string a;
    a = "test -e file/text.txt";
    p.addTree(test.TESTINGinputTree(a));
    EXPECT_EQ(p.next(true), "[ -e file/text.txt ]");
    a = "[-e file/second.txt]";
    p.addTree(test.TESTINGinputTree(a));
    EXPECT_EQ(p.next(false), "[ -e file/second.txt ]");
}

TEST(ReadTest, TestBracketSpace) {
    Read test;
    Process p;
    std::string a;
    a = "[   -e file/text.txt    ]";
    p.addTree(test.TESTINGinputTree(a));
    EXPECT_EQ(p.next(true), "[ -e file/text.txt ]");
}

TEST(ReadTest, SubTrees) {
    Read test;
    Process p;
    std::string a;
    a = "(echo a || echo b) && (echo c; echo d)";
    p.addTree(test.TESTINGinputTree(a));
    EXPECT_EQ(p.next(true), "echo a");
    EXPECT_EQ(p.next(true), "echo c");
    EXPECT_EQ(p.next(false), "echo d");
}

TEST(ReadTest, MultiTest) {
    Read test;
    Process p;
    std::string a;
    a = "(echo a || (echo b && echo c))";
    p.addTree(test.TESTINGinputTree(a));
    EXPECT_EQ(p.next(true), "echo a");
    EXPECT_EQ(p.next(false), "echo b");
    EXPECT_EQ(p.next(true), "echo c");
}

/*
TEST(ReadTest, SubQuoteTree) {
    Read test;
    Process p;
    std::string a;
    a = "(echo a && (echo \"b total\"))";
    p.addTree(test.TESTINGinputTree(a));
    EXPECT_EQ(p.next(true), "echo a");
    EXPECT_EQ(p.next(true), "echo \"b total\"))");
}

TEST(ReadTest, TripleTree) {
    Read test;
    Process p;
    std::string a;
    a = "(echo a && ( echo b && ( echo c )))";
    p.addTree(test.TESTINGinputTree(a));
    EXPECT_EQ(p.next(true), "echo a");
    EXPECT_EQ(p.next(true), "echo b");
    EXPECT_EQ(p.next(true), "echo c");
}*/

#endif
