#include "forma_core.hpp"

#include <string>

#include <pessum/pessum.hpp>

#include "gl_headers.hpp"

void forma::InitForma() {
  pessum::Log(pessum::INFO, "Forma Version: %i.%i.%i", "forma::InitForma",
              FORMA_VERSION_MAJOR, FORMA_VERSION_MINOR, FORMA_VERSION_PATCH);
  InitGlfw();
  pessum::Log(pessum::INFO, "OpenGL Version: %i.%i", "forma::InitGlfw",
              GL_VERSION_MAJOR, GL_VERSION_MINOR);
}

void forma::TermForma() {
  TermGlad();
  TermGlfw();
}

void forma::InitGlfw() {
  glfwSetErrorCallback(GlfwError);
  if (!glfwInit()) {
    pessum::Log(pessum::ERROR, "Failed to initialize GLFW",
                "forma::InitGlfw()");
  } else {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  }
}

void forma::InitGlad() {}

void forma::TermGlfw() { glfwTerminate(); }

void forma::TermGlad() {}

void forma::GetVersion(int& major, int& minor, int& patch) {
  major = FORMA_VERSION_MAJOR;
  minor = FORMA_VERSION_MINOR;
  patch = FORMA_VERSION_PATCH;
}

void forma::GlfwError(int error_code, const char* error) {
  std::string str(error);
  pessum::Log(pessum::ERROR, "[%i]%s", "GLFW", error_code, error);
}

void forma::GladError() {}
