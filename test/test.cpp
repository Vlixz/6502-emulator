extern "C"{

#include <functions.h>

}

#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  
  // Expect equality.
  EXPECT_EQ(add(7, 3), 10);
}


