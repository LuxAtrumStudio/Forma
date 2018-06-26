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
}  // namespace forma

void forma::input::PollEvents() { glfwPollEvents(); }

void forma::input::KeyCallBack(GLFWwindow* win, int key, int scan_code,
                               int action, int mode) {
  key_data_[win].push_back(std::array<int, 4>{{key, scan_code, action, mode}});
}

int forma::input::GetKeyState(GLFWwindow* win, unsigned key){
  return glfwGetKey(win, key);
}

std::vector<std::array<int, 4>> forma::input::GetKeyData(GLFWwindow* win) {
  std::vector<std::array<int, 4>> key_vec = key_data_[win];
  key_data_[win].clear();
  return key_vec;
}

std::array<int, 4> forma::input::GetNextKey(GLFWwindow* win) {
  if (key_data_[win].size() > 0) {
    std::array<int, 4> key_data = key_data_[win].back();
    key_data_[win].erase(--(key_data_[win].end()));
    return key_data;
  } else {
    return std::array<int, 4>{{0, 0, 0, 0}};
  }
}

void forma::input::PrependKeyData(GLFWwindow* win,
                                  std::vector<std::array<int, 4>> key_vector) {
  key_data_[win].insert(key_data_[win].begin(), key_vector.begin(),
                        key_vector.end());
}

void forma::input::PrependKeyData(GLFWwindow* win,
                                  std::array<int, 4> key_data) {
  key_data_[win].insert(key_data_[win].begin(), key_data);
}
