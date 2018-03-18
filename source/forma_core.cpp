#include "forma_core.hpp"

#include "error/error.hpp"
#include "gl.hpp"
#include "log/logger.hpp"
#include "window/window.hpp"

namespace forma {
  bool forma_init_ = false, glfw_init_ = false, glad_init_ = false;
}  // namespace forma

void forma::InitForma() {
  logging::Version("forma_core.cpp", "forma::InitForma()",
                   "Forma version: %i.%i", FORMA_VERSION_MAJOR,
                   FORMA_VERSION_MINOR);
  logging::Version("forma_core.cpp", "forma::InitForma()",
                   "OpenGL version: %i.%i", GL_VERSION_MAJOR, GL_VERSION_MINOR);
  InitGlfw();
  window::Window win;
  win.CreateWindow();
  win.MakeCurrent();
  InitGlad();
  win.DestroyWindow();
  if (glfw_init_ == true && glad_init_ == true) {
    forma_init_ = true;
  } else {
    logging::Fatal("forma_core.cpp", "forma::InitForma()",
                   "Failed to initialize Forma");
  }
}

void forma::InitGlad() {
  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false) {
    logging::Fatal("forma_core.cpp", "forma::InitGlad()",
                   "Failed to initialize GLAD");
    glad_init_ = false;
  } else {
    glad_init_ = true;
  }
}

void forma::InitGlfw() {
  glfwSetErrorCallback(error::GlfwErrorHandle);
  if (glfwInit() == false) {
    logging::Fatal("forma_core.cpp", "forma::InitGlfw()",
                   "Failed to initialize GLFW");
  } else {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    logging::Version("forma_core.cpp", "forma::InitGlfw()",
                     "GLFW version: %i.%i.%i", GLFW_VERSION_MAJOR,
                     GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
    glfw_init_ = true;
  }
}

void forma::TermForma() {
  TermGlad();
  TermGlfw();
  forma_init_ = false;
}

void forma::TermGlad() { glad_init_ = false; }

void forma::TermGlfw() {
  glfwTerminate();
  glfw_init_ = false;
}

bool forma::FormaInit() { return forma_init_; }

bool forma::GladInit() { return glad_init_; }

bool forma::GlfwInit() { return glfw_init_; }

void forma::OpenGLVersion(int& major, int& minor) {
  major = GL_VERSION_MAJOR;
  minor = GL_VERSION_MINOR;
}

void forma::GLFWVersion(int& major, int& minor) {
  major = GLFW_VERSION_MAJOR;
  minor = GLFW_VERSION_MINOR;
}

void forma::FormaVersion(int& major, int& minor) {
  major = FORMA_VERSION_MAJOR;
  minor = FORMA_VERSION_MINOR;
}
