#include "forma/gl/gl.hpp"

static bool is_loaded_ = false;

bool forma::gl::load_gl() {
  if (is_loaded_) return true;
  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) != 0) {
    is_loaded_ = true;
    return true;
  };
  return false;
}
