#ifndef FORMA_INPUT_HPP
#define FORMA_INPUT_HPP
#include <queue>
#include <vector>
#include "gl_headers.hpp"
#include "window/window.hpp"
namespace forma {
  extern std::vector<std::tuple<GLFWwindow*, int, int, int, int>> key_calls;
  void KeyCallback(GLFWwindow* win, int key, int scan_code, int action,
                   int mode);
  void HandleKey(Window win);
}
#endif
