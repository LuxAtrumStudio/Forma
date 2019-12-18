#include "gl.hpp"

#include <GLFW/glfw3.h>

#include "forma/log.hpp"

static bool glfw_is_init = false, gl_is_loaded = false;

void glfw_error_callback(int error_code, const char* description) {
  forma::logger::error("GLFW [{}]: {}", error_code, description);
}

void forma::gl::set_error_callback() {
  glfwSetErrorCallback(glfw_error_callback);
}
void forma::gl::log_glfw_warn() {
  const char* glfw_err;
  glfwGetError(&glfw_err);
  forma::logger::warn("GLFW: {}", glfw_err);
}
void forma::gl::log_glfw_error() {
  const char* glfw_err;
  glfwGetError(&glfw_err);
  forma::logger::error("GLFW: {}", glfw_err);
}
void forma::gl::log_glfw_critical() {
  const char* glfw_err;
  glfwGetError(&glfw_err);
  forma::logger::critical("GLFW: {}", glfw_err);
}
bool forma::gl::init_glfw() {
  if (glfw_is_init) return true;
  set_error_callback();
  if (!glfwInit()) {
    log_glfw_critical();
    return false;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfw_is_init = true;
  return true;
}
bool forma::gl::term_glfw() {
  if (!glfw_is_init) return true;
  glfwTerminate();
  glfw_is_init = false;
  return true;
}
bool forma::gl::load_gl() {
  if (gl_is_loaded) return true;
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    LCRITICAL("Failed to load OpenGL using GLAD");
    return false;
  }
  gl_is_loaded = true;
  return true;
}
