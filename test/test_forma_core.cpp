#include "forma_core.hpp"

#include <iostream>

#include "gtest/gtest.h"

#include "gl.hpp"

TEST(FormaCore, OpenGLVersion) {
  int major = 0, minor = 0;
  forma::OpenGLVersion(major, minor);
  EXPECT_EQ(major, GL_VERSION_MAJOR);
  EXPECT_EQ(minor, GL_VERSION_MINOR);
}

TEST(FormaCore, GLFWVersion) {
  int major = 0, minor = 0;
  forma::GLFWVersion(major, minor);
  EXPECT_EQ(major, GLFW_VERSION_MAJOR);
  EXPECT_EQ(minor, GLFW_VERSION_MINOR);
}

TEST(FormaCore, FormaVersion) {
  int major = 0, minor = 0;
  forma::FormaVersion(major, minor);
  EXPECT_EQ(major, FORMA_VERSION_MAJOR);
  EXPECT_EQ(minor, FORMA_VERSION_MINOR);
}
