#include "window/callback.hpp"

#include "gl.hpp"

void forma::window::FramebufferSizeCallback(GLFWwindow* window, int width,
                                            int height) {
  glfwMakeContextCurrent(window);
  glViewport(0, 0, width, height);
}
