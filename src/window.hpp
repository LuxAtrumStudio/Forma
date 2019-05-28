#ifndef FORMA_WINDOW_HPP_
#define FORMA_WINDOW_HPP_

#include <string>

#include <GLFW/glfw3.h>

namespace forma {
  class Window {
   public:
    Window();
    Window(const unsigned& width_px, const unsigned& height_px,
           const std::string& name, bool full_screen = false);
    virtual ~Window();

   private:
    GLFWwindow* window_ = NULL;

    std::string name_;
    unsigned width_, height_;
  };
}  // namespace forma

#endif  // FORMA_WINDOW_HPP_
