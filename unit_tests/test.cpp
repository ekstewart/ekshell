#include "gtest/gtest.h"

#include "pipe_test.cpp"
#include "deco_test.cpp"
#include "exec_test.cpp"
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
