#include "context.hpp"

#include <GLFW/glfw3.h>

namespace forma {
  namespace window {
    GLFWwindow* current_context_ = NULL;
  } // namespace window
} // namespace forma

void forma::window::make_context_current(GLFWwindow* win){
  if (current_context_ != win){
    glfwMakeContextCurrent(win);
  }
}
