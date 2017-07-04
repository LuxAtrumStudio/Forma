#include "forma_core.hpp"

#include <string>

#include <pessum/pessum.hpp>

#include "gl_headers.hpp"
#include "window/window.hpp"

void forma::InitForma() {
  pessum::Log(pessum::INFO, "Forma Version: %i.%i.%i", "forma::InitForma",
              FORMA_VERSION_MAJOR, FORMA_VERSION_MINOR, FORMA_VERSION_PATCH);
  InitGlfw();
  Window win;
  InitGlad();
  win.Delete();
  pessum::Log(pessum::INFO, "OpenGL Version: %i.%i", "forma::InitGlfw",
              GL_VERSION_MAJOR, GL_VERSION_MINOR);
}

void forma::TermForma() {
  TermGlad();
  TermGlfw();
}

void forma::InitGlfw() {
  glfwSetErrorCallback(GlfwError);
  if (glfwInit() == false) {
    pessum::Log(pessum::ERROR, "Failed to initialize GLFW",
                "forma::InitGlfw()");
  } else {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  }
}

void forma::InitGlad() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    pessum::Log(pessum::ERROR, "Failed to initialized GLAD",
                "forma::InitGlad()");
  }
}

void forma::TermGlfw() { glfwTerminate(); }

void forma::TermGlad() {}

void forma::GetVersion(int& major, int& minor, int& patch) {
  major = FORMA_VERSION_MAJOR;
  minor = FORMA_VERSION_MINOR;
  patch = FORMA_VERSION_PATCH;
}

void forma::GlfwError(int error_code, const char* error) {
  pessum::Log(pessum::ERROR, "[%i]%s", "GLFW", error_code, error);
}

void forma::GladError() {}
