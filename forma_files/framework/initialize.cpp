#include <pessum.h>
#include "../gl_headers.hpp"
#include "initialize.hpp"

void forma::framework::InitGlfw() {
  if (!glfwInit()) {
    pessum::logging::Log("fatal", "Failed to initialize GLFW",
                         "forma/framework/initialize/InitGlfw");
  }
  GlfwVersion();
  GlfwProfile();
}

void forma::framework::InitGlew() {
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::string log_string = "Failed to initialize GLEW: ";
    printf("GLEW ERROR: %s\n", glewGetErrorString(err));
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
