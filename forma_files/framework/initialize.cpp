#include "../gl_headers.hpp"
#include "initialize.hpp"
#include <pessum.h>

void forma::framework::InitGlfw() {
  if (!glfwInit()) {
    pessum::logging::Log("fatal", "Failed to initialize GLFW",
                         "forma/framework/initialize/InitGlfw");
  }
}

void forma::framework::InitGlew() {
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    pessum::logging::Log("fatal", "Failed to initialize GLEW",
                         "forma/framework/initialize/InitGlew");
  }
}

void forma::framework::GlfwVersion(int major, int minor) {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
  pessum::logging::Log("info",
                       "Set OpenGL version to " + std::to_string(major) + "." +
                           std::to_string(minor),
                       "forma/framework/initialize/GlfwVersion");
}

void forma::framework::GlfwProfile() {
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void forma::framework::SetViewPort(int width, int height) {
  glViewport(0, 0, width, height);
}
