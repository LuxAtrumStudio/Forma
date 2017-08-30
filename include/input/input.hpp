#ifndef FORMA_INPUT_INPUT_HPP
#define FORMA_INPUT_INPUT_HPP

#include <array>
#include <vector>

#include "../gl.hpp"

namespace forma {
  namespace input {
    void PollEvents();
    void KeyCallBack(GLFWwindow* win, int key, int scan_code, int action,
                     int mode);
    std::vector<std::array<int, 4>> GetKeyData(GLFWwindow* win);
  }  // namespace input
}  // namespace forma

#endif /* ifndef FORMA_INPUT_INPUT_HPP */
