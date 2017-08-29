#include "forma_core.hpp"

#include "error/error.hpp"
#include "gl.hpp"
#include "log/log.hpp"

void forma::InitForma() {
  log::Log(log::VERSION, "Forma verison: %i.%i.%i", "forma::InitForma",
           FORMA_VERSION_MAJOR, FORMA_VERSION_MINOR, FORMA_VERSION_PATCH);
  log::Log(log::VERSION, "OpenGL version: %i.%i", "forma::InitForma",
           GL_VERSION_MAJOR, GL_VERSION_MINOR);
  InitGlfw();
  // InitGlad();
}

void forma::InitGlad() {
  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false) {
    log::Log(log::FATAL, "Failed to initialize GLAD", "forma::InitGlad");
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
  }
}

void forma::TermForma() {
  TermGlad();
  TermGlfw();
}

void forma::TermGlad() {}

void forma::TermGlfw() { glfwTerminate(); }
