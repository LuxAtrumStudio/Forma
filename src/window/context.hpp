#ifndef FORMA_WINDOW_CONTEXT_HPP_
#define FORMA_WINDOW_CONTEXT_HPP_

#include <GLFW/glfw3.h>

namespace forma {
  namespace window {
    void make_context_current(GLFWwindow* win);

    extern GLFWwindow* current_context_;
  }  // namespace window
}  // namespace forma

#endif  // FORMA_WINDOW_CONTEXT_HPP_
