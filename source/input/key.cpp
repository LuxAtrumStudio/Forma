#include "input/key.hpp"

#include <array>
#include <map>
#include <vector>

#include "gl.hpp"

namespace forma {
  namespace input {
    static std::map<GLFWwindow*, std::vector<std::array<int, 4>>> key_event_data_;
  } // namespace input
} // namespace forma

void forma::input::KeyCallback(GLFWwindow* win, int key, int scan_code, int action, int mode){
  key_event_data_[win].push_back(std::array<int, 4>{{key, scan_code, action, mode}});
}
