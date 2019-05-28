#include "glad.hpp"

#include "../glad/glad.h"

#include <GLFW/glfw3.h>

#include "../logger.hpp"

const bool loaded_ = false;

void forma::window::init_glad() {
  if(loaded_) return;
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    forma::log::fatal("Failed to load OpenGL functions");
  }
}
