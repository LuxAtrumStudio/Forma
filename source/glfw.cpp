#include "glfw.hpp"

#include "gl_headers.hpp"

void forma::GlfwWindowHint(int target, int hint) {
  glfwWindowHint(target, hint);
}
