#include "input/input.hpp"

#include "gtest/gtest.h"

TEST(FormaInput, GetKeyData) {
  std::vector<std::array<int, 4>> data = forma::input::GetKeyData(NULL);
  EXPECT_EQ(data.size(), 0);
}
