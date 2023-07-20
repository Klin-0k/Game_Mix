#include <gtest/gtest.h>
// clang-format off
#include <tests/InterfaceTests.h>
#include <tests/Game1Test.h>
#include <tests/Game2Test.h>
// clang-format on

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}