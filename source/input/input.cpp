#include "input/input.hpp"

#include <array>
#include <vector>

#include "gl.hpp"

namespace forma {
  namespace input {
    std::vector<std::pair<GLFWwindow*, std::array<int, 4>>> key_data_;
  }  // namespace input
}  // namespace form

void forma::input::PollEvents() { glfwPollEvents(); }

std::vector<std::array<int, 4>> forma::input::GetKeyData(GLFWwindow* win) {
  std::vector<std::array<int, 4>> key_vec;
  for (std::vector<std::pair<GLFWwindow*, std::array<int, 4>>>::iterator it =
           key_data_.begin();
       it != key_data_.end(); ++it) {
    if (it->first == win) {
      key_vec.push_back(it->second);
    }
  }
  return key_vec;
}
