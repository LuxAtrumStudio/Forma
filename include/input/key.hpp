#ifndef FORMA_INPUT_KEY_HPP_
#define FORMA_INPUT_KEY_HPP_

#include <array>
#include "../gl.hpp"

namespace forma {
  namespace input {
    typedef typename std::array<int, 4> KeyData;
    void KeyCallback(GLFWwindow* win, int key, int scan_code, int action, int mode);
  } // namespace input
} // namespace forma

#endif  // FORMA_INPUT_KEY_HPP_
