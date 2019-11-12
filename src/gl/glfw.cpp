#include "forma/gl/glfw.hpp"

#include "forma/log.hpp"

void forma::gl::glfw_error_callback(int error_code, const char* description) {
  logger::error("GLFW [{}]: {}", error_code, description);
}
