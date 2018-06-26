#ifndef FORMA_INPUT_INPUT_HPP
#define FORMA_INPUT_INPUT_HPP

#include <array>
#include <vector>

#include "../gl.hpp"

namespace forma {
  namespace input {
    typedef typename std::array<int, 4> KeyData;
    void PollEvents();
    void KeyCallBack(GLFWwindow* win, int key, int scan_code, int action,
                     int mode);
    int GetKeyState(GLFWwindow* win, unsigned key);
    std::vector<std::array<int, 4>> GetKeyData(GLFWwindow* win);
    std::array<int, 4> GetNextKey(GLFWwindow* win);
    void PrependKeyData(GLFWwindow* win, std::vector<std::array<int, 4>> key_vector);
    void PrependKeyData(GLFWwindow* win, std::array<int, 4> key_data);
  }  // namespace input
}  // namespace forma

#endif /* ifndef FORMA_INPUT_INPUT_HPP */
