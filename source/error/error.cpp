#include "error/error.hpp"

#include "log/log.hpp"

void forma::error::GlfwErrorHandle(int error_num, const char* error_msg) {
  log::Log(log::ERROR, "(%i) %s", "GLFW", error_num, error_msg);
}
