#include "forma/graphics/window.hpp"

#include "forma/forma.hpp"
#include "forma/gl/gl.hpp"
#include "forma/log.hpp"
#include "forma/version.hpp"

static GLFWwindow* window_ = NULL;
static std::size_t width_ = 0, height_ = 0;
static std::string title_;

bool forma::graphics::window::create_window(const std::size_t& w,
                                            const std::size_t& h,
                                            const std::string& title,
                                            bool fullscreen) {
  if (window_ != NULL) destroy_window();
  width_ = w;
  height_ = h;
  title_ = title;
  if (!is_initalized() && !forma::initalize(true)) return false;
  if (fullscreen)
    window_ = glfwCreateWindow(width_, height_, title_.c_str(),
                               glfwGetPrimaryMonitor(), NULL);
  else
    window_ = glfwCreateWindow(width_, height_, title_.c_str(), NULL, NULL);
  if (window_ == NULL) {
    LERROR("Failed to create GLFW window \"{}\"", title);
    return false;
  }
  gl::make_current(window_);
  if (!gl::load_gl()) {
    glfwDestroyWindow(window_);
    return false;
  }
  glfwSetFramebufferSizeCallback(window_, GLFW_framebuffer_size_callback);
  return true;
}

bool forma::graphics::window::destroy_window() {
  if (window_ == NULL) return true;
  glfwDestroyWindow(window_);
  window_ = NULL;
  title_ = std::string();
  width_ = 0;
  height_ = 0;
  return true;
}

bool forma::graphics::window::valid() { return window_ != NULL; }
bool forma::graphics::window::should_close() {
  if (window_ == NULL) return true;
  return glfwWindowShouldClose(window_);
}

void forma::graphics::window::swap() {
  if(window_ == NULL) return;
  glfwSwapBuffers(window_);
}

bool forma::graphics::window::resize(const std::size_t& w,
                                     const std::size_t& h) {
  if (window_ == NULL) return false;
  width_ = w;
  height_ = h;
  glViewport(0, 0, width_, height_);
  return true;
}

void forma::graphics::window::GLFW_framebuffer_size_callback(GLFWwindow*, int w,
                                                             int h) {
  width_ = w;
  height_ = h;
  glViewport(0, 0, width_, height_);
}
