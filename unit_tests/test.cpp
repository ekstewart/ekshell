#include "gtest/gtest.h"

#include "CCC_test.cpp"
#include "cmd_test.cpp"
#include "pipe_test.cpp"
#include "deco_test.cpp"
#include "reference_test.cpp"
//#include "read_test.cpp"
#include "exec_test.cpp"
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
