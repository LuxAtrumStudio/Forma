#ifndef FORMA_GRAPHICS_WINDOW_HPP_
#define FORMA_GRAPHICS_WINDOW_HPP_

#include <cstdlib>
#include <string>

#include "../gl/gl.hpp"

namespace forma {
  namespace graphics {
    namespace window {
      bool create_window(const std::size_t& w, const std::size_t& h,
                         const std::string& title, bool fullscreen = false);
      bool destroy_window();

      bool valid();
      bool should_close();

      void swap();

      bool resize(const std::size_t& w, const std::size_t& h);
      void GLFW_framebuffer_size_callback(GLFWwindow*, int w, int h);
    }  // namespace window
  }    // namespace graphics
}  // namespace forma

#endif  // FORMA_GRAPHICS_WINDOW_HPP_
