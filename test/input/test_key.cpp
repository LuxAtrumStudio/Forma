#include "input/key.hpp"

#include "gtest/gtest.h"

#include "gl.hpp"

TEST(FormaInputKey, CheckKeys) {
  EXPECT_EQ(forma::input::KEY_ESCAPE, GLFW_KEY_ESCAPE);
}
