#include "forma.hpp"

#include <GLFW/glfw3.h>

#include "logger.hpp"

bool forma::init() {
#ifndef DEV
  forma::log::Default()->set_activation(forma::log::FATAL | forma::log::ERROR |
                                        forma::log::INFO);
#endif
  forma::log::version("FORMA v.%d.%d", FORMA_VERSION_MAJOR,
                      FORMA_VERSION_MINOR);
  glfwInit();
  glfwSetErrorCallback(forma::glfw_error_callback);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  return true;
}

void forma::glfw_error_callback(int error, const char* description){
  forma::log::Logger::get()->_log(forma::log::ERROR, description, "GLFW", "", error);
}
