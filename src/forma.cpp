#include "forma/forma.hpp"

#include <bitset>
#include <cstdlib>
#include <functional>
#include <string>

#include "forma/gl/gl.h"
#include "forma/log.hpp"
#include "forma/version.hpp"
#include "forma/key.hpp"

static GLFWwindow* window_ = NULL;
static std::size_t width_ = 0, height_ = 0;
static std::string title_ = "";

static std::size_t target_fps = 60;

static std::function<void(const float&)> update_;

void glfw_error_callback(int error_code, const char* description) {
  forma::logger::error("GLFW [{}]: {}", error_code, description);
}
void glfw_framebuffer_size_callback(GLFWwindow*, int w, int h) {
  width_ = w;
  height_ = h;
  glViewport(0, 0, width_, height_);
}

bool forma::initalize_logger(const bool& console_logger) {
  return logger::initalize_logger(console_logger);
}

bool forma::create_window(const std::size_t& w, const std::size_t& h,
                          const std::string& title, bool fullscreen) {
  if (!logger::is_initalized() && !forma::logger::initalize_logger(false))
    return false;
  LINFO("FORMA v{}.{}.{}", FORMA_VERSION_MAJOR, FORMA_VERSION_MINOR,
        FORMA_VERSION_PATCH);
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit()) {
    const char* glfw_err;
    glfwGetError(&glfw_err);
    LCRITICAL("Failed to initalize GLFW: {}", glfw_err);
    return false;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, FORMA_GL_VERSION_MAJOR);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, FORMA_GL_VERSION_MINOR);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  int glfw_major, glfw_minor, glfw_patch;
  glfwGetVersion(&glfw_major, &glfw_minor, &glfw_patch);
  LINFO("GLFW v{}.{}.{}", glfw_major, glfw_minor, glfw_patch);
  LINFO("OpenGL v{}.{}", FORMA_GL_VERSION_MAJOR, FORMA_GL_VERSION_MINOR);
  width_ = w;
  height_ = h;
  title_ = title;
  if (fullscreen)
    window_ = glfwCreateWindow(width_, height_, title_.c_str(),
                               glfwGetPrimaryMonitor(), NULL);
  else
    window_ = glfwCreateWindow(width_, height_, title_.c_str(), NULL, NULL);
  if (window_ == NULL) {
    LERROR("Failed to create GLFW window \"{}\"", title);
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(window_);
  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
    LERROR("Failed to load GL with GLAD");
    glfwDestroyWindow(window_);
    glfwTerminate();
    return false;
  };
  glfwSetFramebufferSizeCallback(window_, glfw_framebuffer_size_callback);
  return true;
}

bool forma::close_window() {
  if (window_ != NULL) return true;
  glfwDestroyWindow(window_);
  glfwTerminate();
  return true;
}

void forma::set_update(const std::function<void(const float&)> update) {
  update_ = update;
}

void forma::run() {
  if (update_ == nullptr) {
    LERROR("Must define an update function");
    return;
  }
  while (!glfwWindowShouldClose(window_)) {
    float ds = 0.0;
    glfwPollEvents();
    update_(ds);
    glfwSwapBuffers(window_);
  }
}

void forma::run(const std::function<void(const float&)> update) {
  update_ = update;
  run();
}

bool forma::is_key_down(const Key& key){

}
