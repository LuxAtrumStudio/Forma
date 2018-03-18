#include "input/input.hpp"

#include <array>
#include <map>
#include <vector>

#include "gl.hpp"
#include "log/logger.hpp"

namespace forma {
  namespace input {
    std::map<GLFWwindow*, std::vector<std::array<int, 4>>> key_data_;
  }  // namespace input
}  // namespace form

void forma::input::PollEvents() { glfwPollEvents(); }

void forma::input::KeyCallBack(GLFWwindow* win, int key, int scan_code,
                               int action, int mode) {
  key_data_[win].push_back(std::array<int, 4>{{key, scan_code, action, mode}});
}

std::vector<std::array<int, 4>> forma::input::GetKeyData(GLFWwindow* win) {
  std::vector<std::array<int, 4>> key_vec = key_data_[win];
  key_data_[win].clear();
  return key_vec;
}
