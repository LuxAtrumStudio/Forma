#include <pessum.h>
#include <string>
#include "forma.hpp"
#include "gl_headers.hpp"
#include "window/window.hpp"

forma::Window forma::InitForma(std::string name, int width, int height) {
  InitGlfw();
  Window win;
  win.CreateWindow(width, height, name);
  InitGlew();
  return (win);
}

void forma::TermForma() {}

void forma::InitGlfw(int v_major, int v_minor) {
  glfwSetErrorCallback(GlError);
  if (!glfwInit()) {
    pessum::Log(pessum::ERROR, "Failed to initialize GLFW", "forma/InitGlfw");
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, v_major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, v_minor);
  pessum::Log(pessum::INFO, "OpenGl Version: %i.%i", "forma/InitGlfw", v_major,
              v_minor);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void forma::InitGlew() {
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    pessum::Log(pessum::ERROR, "Failed to initialize GLEW", "forma/InitGlew");
    GlError(err);
  }
}

void forma::GlError(int error_code, const char* error) {
  std::string error_str = error;
  pessum::Log(pessum::ERROR, "<%i>" + error_str, "GLFW", error_code);
}

void forma::GlError(GLenum err) {
  pessum::Log(pessum::ERROR, "%s", "GLEW", glewGetErrorString(err));
}

void forma::SetWindowPreset(int setting, bool value) {
  glfwWindowHint(setting, value);
}
