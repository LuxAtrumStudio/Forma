#include "error/error.hpp"

#include "gtest/gtest.h"

#include "log/log.hpp"

TEST(FormaError, GlfwErrorHandle) {
  forma::error::GlfwErrorHandle(404, "Error not found");
  std::pair<unsigned int, std::string> entry =
      forma::log::FGetLog(forma::log::ERROR);
  EXPECT_EQ(entry.first, forma::log::ERROR);
  EXPECT_EQ(entry.second, "[ERROR][(404) Error not found][GLFW]");
}
