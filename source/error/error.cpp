#include "error/error.hpp"

#include "log/logger.hpp"

void forma::error::GlfwErrorHandle(int error_num, const char* error_msg) {
  logging::Error("GLFW", std::to_string(error_num), "%s", error_msg);
}
