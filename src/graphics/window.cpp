#include "forma/graphics/window.hpp"

#include <cstdlib>
#include <string>

#include "forma/gl/gl.hpp"
#include "forma/log.hpp"

forma::graphics::Window::Window(const std::size_t& w, const std::size_t& h,
                                const std::string& title, bool fullscreen)
    : width_(w),
      height_(h),
      title_(title),
      monitor_(fullscreen ? glfwGetPrimaryMonitor() : NULL),
      window_(
          glfwCreateWindow(width_, height_, title_.c_str(), monitor_, NULL)) {
  if (window_ == NULL) {
    LERROR("Failed to create GLFW window \"{}\"", title_);
  } else {
    gl::make_current(window_);
    if (!gl::load_gl()) {
      glfwDestroyWindow(window_);
      window_ = NULL;
    }
  }
}

forma::graphics::Window::~Window() {
  if (window_ == NULL) return;
  glfwDestroyWindow(window_);
  window_ = NULL;
}
