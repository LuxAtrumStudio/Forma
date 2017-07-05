#ifndef FORMA_WINDOW_WINDOW_EXTERNAL_HPP
#define FORMA_WINDOW_WINDOW_EXTERNAL_HPP

#include <memory>

#include "../gl_headers.hpp"
#include "window.hpp"

namespace forma {
  namespace window {
    void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
  }  // namespace window
}  // namespace forma
#endif
