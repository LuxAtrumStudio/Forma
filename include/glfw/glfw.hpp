#ifndef FORMA_GLFW_GLFW_HPP
#define FORMA_GLFW_GLFW_HPP

#include "gl.hpp"

namespace forma {
  namespace gl {
    void GlfwWindowHint(int target, int hint) { glfwWindowHint(target, hint); }
  }  // namespace gl
}  // namespace forma

#endif /* ifndef FORMA_GLFW_GLFW_HPP */
