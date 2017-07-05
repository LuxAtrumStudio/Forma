#include "window_external.hpp"

#include <pessum/pessum.hpp>

#include "../gl_headers.hpp"
#include "window.hpp"

void forma::window::FramebufferSizeCallback(GLFWwindow* window, int width,
                                            int height) {
  pessum::Log(pessum::DATA, "%ix%i", "", width, height);
  glViewport(0, 0, width, height);
}
