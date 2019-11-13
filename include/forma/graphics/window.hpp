#ifndef FORMA_GRAPHICS_WINDOW_HPP_
#define FORMA_GRAPHICS_WINDOW_HPP_

#include <cstdlib>
#include <string>

#include "../gl/gl.hpp"

namespace forma {
  namespace graphics {
    class Window {
     public:
      Window(const std::size_t& w, const std::size_t& h,
             const std::string& title, bool fullscreen = false);
      ~Window();

      inline void destroy() {
        if (window_ == NULL) return;
        glfwDestroyWindow(window_);
        window_ = NULL;
      }
      inline constexpr bool valid() const { return window_ != NULL; }

     private:
      std::size_t width_, height_;
      std::string title_;
      GLFWmonitor* monitor_;
      GLFWwindow* window_;
    };
  }  // namespace graphics
}  // namespace forma

#endif  // FORMA_GRAPHICS_WINDOW_HPP_
