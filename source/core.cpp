#include "core.hpp"

#include <estl/logger.hpp>

#include "gl.hpp"

namespace forma {
  static bool forma_init_ = false, glfw_init_ = false, glad_init_ = false;
}  // namespace forma

void GlfwErrorHandle(int error_num, const char* error_msg) {
  estl::logger::Logger::Get()->GetLogger()->_LogError(error_msg, "GLFW", "",
                                                      error_num);
}

bool forma::InitForma() {
#if defined DEV
  estl::logger::Logger::Get()->SetDefault(estl::logger::Logger::CONSOLE);
#else
  estl::logger::Logger::Get()->SetDefault(estl::logger::Logger::DAILY);
#endif
  estl::logger::Version("Forma Version: %i.%i", FORMA_VERSION_MAJOR,
                        FORMA_VERSION_MINOR);
  estl::logger::Version("OpenGL Version: %i.%i", GL_VERSION_MAJOR,
                        GL_VERSION_MINOR);
  InitGlfw();
  forma_init_ = true;
  return true;
}

bool forma::InitGlad() {
  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false) {
    estl::logger::Fatal("Failed to initialize GLAD");
    return false;
  } else {
    return true;
  }
}

bool forma::InitGlfw() {
  glfwSetErrorCallback(GlfwErrorHandle);
  if (glfwInit() == false) {
    estl::logger::Fatal("Failed to initialize GLFW");
    return false;
  } else {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    estl::logger::Version("GFLW Version: %i.%i", GLFW_VERSION_MAJOR,
                          GLFW_VERSION_MINOR);
    glfw_init_ = true;
    return true;
  }
}

bool forma::TermForma() {
  TermGlad();
  TermGlfw();
  forma_init_ = false;
  return true;
}

bool forma::TermGlad() { return true; }

bool forma::TermGlfw() {
  glfwTerminate();
  glfw_init_ = false;
  return true;
}

bool forma::IsInitForma() { return forma_init_; }
bool forma::IsInitGlad() { return glad_init_; }
bool forma::IsInitGlfw() { return glfw_init_; }
