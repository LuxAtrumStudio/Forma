#include "forma_core.hpp"

#include "error/error.hpp"
#include "gl.hpp"
#include "log/log.hpp"
#include "window/window.hpp"

namespace forma {
  bool forma_init_ = false, glfw_init_ = false, glad_init_ = false;
}  // namespace forma

void forma::InitForma() {
  log::Log(log::VERSION, "Forma verison: %i.%i.%i", "forma::InitForma",
           FORMA_VERSION_MAJOR, FORMA_VERSION_MINOR, FORMA_VERSION_PATCH);
  log::Log(log::VERSION, "OpenGL version: %i.%i", "forma::InitForma",
           GL_VERSION_MAJOR, GL_VERSION_MINOR);
  InitGlfw();
  window::Window win;
  win.CreateWindow();
  win.MakeCurrent();
  InitGlad();
  win.DestroyWindow();
  if (glfw_init_ == true && glad_init_ == true) {
    forma_init_ = true;
  } else {
    log::Log(log::FATAL, "Failed to initialize Forma", "forma::InitForma");
  }
}

void forma::InitGlad() {
  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false) {
    log::Log(log::FATAL, "Failed to initialize GLAD", "forma::InitGlad");
  } else {
    glad_init_ = true;
  }
}

void forma::InitGlfw() {
  glfwSetErrorCallback(error::GlfwErrorHandle);
  if (glfwInit() == false) {
    log::Log(log::FATAL, "Failed to initialize GLFW", "forma::InitGlfw");
  } else {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    log::Log(log::VERSION, "GLFW verison: %i.%i.%i", "forma::InitGlfw",
             GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
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
