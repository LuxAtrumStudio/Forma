#include <pessum.h>
#include <iostream>
#include "../gl_headers.hpp"
#include "input.hpp"

namespace forma {
  std::vector<std::tuple<GLFWwindow*, int, int, int, int>> key_calls;
}

void forma::KeyCallback(GLFWwindow* win, int key, int scan_code, int action,
                        int mode) {
  key_calls.push_back(std::make_tuple(win, key, scan_code, action, mode));
}

void forma::HandleKey(Window win) {
  for (int i = 0; i < key_calls.size(); i++) {
    if (*win() == std::get<0>(key_calls[i])) {
      win.KeyPress(key_calls[i]);
      key_calls.erase(key_calls.begin() + i);
    }
  }
}
