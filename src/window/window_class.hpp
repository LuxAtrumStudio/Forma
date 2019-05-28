#ifndef FORMA_WINDOW_WINDOW_CLASS_HPP_
#define FORMA_WINDOW_WINDOW_CLASS_HPP_

#include <string>

#include <GLFW/glfw3.h>

#include "../glm/glm.hpp"

namespace forma {
  class Window {
   public:
    Window();
    Window(const unsigned& width_px, const unsigned& height_px,
           const std::string& name, bool full_screen = false);
    virtual ~Window();

    void set_window_should_close(bool val);
    bool window_should_close();

    void update();

    bool should_close = false;

    glm::vec4 clear_color;

   private:
    GLFWwindow* window_ = NULL;

    std::string name_;
    unsigned width_, height_;

  };
}  // namespace forma

#endif  // FORMA_WINDOW_WINDOW_CLASS_HPP_
