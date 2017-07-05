#ifndef FORMA_INPUT_INPUT_HPP
#define FORMA_INPUT_INPUT_HPP

#include "../window/window_headers.hpp"

#include "../gl_headers.hpp"

namespace forma {
  namespace input {
    void KeyCallback(GLFWwindow* window, int key, int scan_code, int action,
                     int mode);
    void HandleKeyCall(window::Window window);
  }  // namespace input
}  // namespace forma
#endif
