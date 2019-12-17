#ifndef REFERENCE_TEST_CPP
#define REFERENCE_TEST_CPP

#include "gtest/gtest.h"
#include "../src/reference.cpp"

TEST(ReferenceTest, AllReferences) {
    Reference r;
    int i;
    EXPECT_EQ(r.check("N", i), 0);
    EXPECT_EQ(r.check("Heyo", i), 0);
    EXPECT_EQ(r.check("&&", i), 1);
    EXPECT_EQ(r.check("||", i), 2);
    EXPECT_EQ(r.check("Heyo;", i), 3);
    EXPECT_EQ(r.check("#", i), 4);
    EXPECT_EQ(r.check("\"", i), 5);
    EXPECT_EQ(r.check("exit", i), 6);
    EXPECT_EQ(r.check("(", i), 7);
    EXPECT_EQ(r.check(")", i), 8);
    EXPECT_EQ(r.check("test", i), 9);
    EXPECT_EQ(r.check("[", i), 10);
    EXPECT_EQ(r.check("]", i), 11);
    EXPECT_EQ(r.check("<", i), 12);
    EXPECT_EQ(r.check(">>", i), 13);
    EXPECT_EQ(r.check(">", i), 14);
    EXPECT_EQ(r.check("|", i), 15);
}

#endif
