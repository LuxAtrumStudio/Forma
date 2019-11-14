#include "forma/graphics/graphics.hpp"

#include "forma/gl/gl.hpp"
#include "forma/graphics/window.hpp"
#include "forma/log.hpp"
#include "forma/version.hpp"

static bool is_initalized_ = false;

bool forma::graphics::initalize() {
  glfwSetErrorCallback(forma::gl::glfw_error_callback);
  if (!glfwInit()) {
    const char* glfw_err;
    glfwGetError(&glfw_err);
    LCRITICAL("Failed to initalize GLFW: {}", glfw_err);
    return false;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, FORMA_GL_VERSION_MAJOR);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, FORMA_GL_VERSION_MINOR);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  int glfw_major, glfw_minor, glfw_patch;
  glfwGetVersion(&glfw_major, &glfw_minor, &glfw_patch);
  LINFO("GLFW v{}.{}.{}", glfw_major, glfw_minor, glfw_patch);
  LINFO("OpenGL v{}.{}", FORMA_GL_VERSION_MAJOR, FORMA_GL_VERSION_MINOR);
  is_initalized_ = true;
  return true;
}

bool forma::graphics::terminate() {
  if (!is_initalized_) return true;
  bool result = true;
  if (window::valid()) result &= window::destroy_window();
  glfwTerminate();
  is_initalized_ = false;
  return result;
}
