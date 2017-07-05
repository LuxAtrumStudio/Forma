#include "input.hpp"

#include <array>
#include <utility>
#include <vector>

#include <pessum/pessum.hpp>

#include "../gl_headers.hpp"
#include "../window/window_headers.hpp"

namespace forma {
  namespace input {
    std::vector<std::pair<GLFWwindow*, std::array<int, 4>>> key_calls_stack;
  }
}

void forma::input::KeyCallback(GLFWwindow* window, int key, int scan_code,
                               int action, int mode) {
  key_calls_stack.insert(
      key_calls_stack.begin(),
      std::make_pair(window,
                     std::array<int, 4>{{key, scan_code, action, mode}}));
}

void forma::input::HandleKeyCall(window::Window window) {
  for (int i = 0; i < key_calls_stack.size(); i++) {
    if (*window() == key_calls_stack[i].first) {
      window.KeyCallback(key_calls_stack[i].second);
      key_calls_stack.erase(key_calls_stack.begin() + i);
    }
  }
}
