#ifndef FORMA_VIDEO_CALLBACK_HPP_
#define FORMA_VIDEO_CALLBACK_HPP_

#include "../gl.hpp"

namespace forma {
  namespace video {
    void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
  } // namespace video
} // namespace forma

#endif  // FORMA_VIDEO_CALLBACK_HPP_
