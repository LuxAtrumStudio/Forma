#include "forma/gl/gl.hpp"

#include "forma/gl/glad.h"

#include <GLFW/glfw3.h>

static bool is_loaded_ = false;
static GLFWwindow* current_ = NULL;

bool forma::gl::load_gl() {
  if (is_loaded_) return true;
  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) != 0) {
    is_loaded_ = true;
    return true;
  };
  return false;
}

void forma::gl::make_current(GLFWwindow* window) {
  if (current_ == window) return;
  glfwMakeContextCurrent(NULL);
  glfwMakeContextCurrent(window);
  current_ = window;
}
