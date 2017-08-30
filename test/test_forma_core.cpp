#include "forma_core.hpp"

#include <iostream>

#include "gtest/gtest.h"

#include "gl.hpp"
#include "log/log.hpp"

TEST(FormaCore, InitForma) {
  forma::InitForma();
  EXPECT_EQ(forma::FormaInit(), true);
  EXPECT_EQ(forma::GlfwInit(), true);
  EXPECT_EQ(forma::GladInit(), true);
  forma::TermForma();
  if (HasFailure() == true) {
    bool first = true;
    std::vector<std::string> logs = forma::log::GetLogs();
    for (size_t i = 0; i < logs.size(); i++) {
      if (first == true) {
        std::cout << "\033[31m[   LOG    ] \033[0m";
        first = false;
      } else {
        std::cout << "\033[31m[          ] \033[0m";
      }
      std::cout << logs[i].c_str() << "\n";
    }
  }
}

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
