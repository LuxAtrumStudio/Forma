#include "window.hpp"

#include <string>

#include <GLFW/glfw3.h>

#include "../logger.hpp"
#include "context.hpp"
#include "glad.hpp"

forma::Window::Window() {}
forma::Window::Window(const unsigned& width_px, const unsigned& height_px,
                      const std::string& name, bool full_screen)
    : should_close(false), clear_color(0.0f, 0.0f, 0.0f, 1.0f) {
  name_ = name;
  if (full_screen) {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    window_ = glfwCreateWindow(mode->width, mode->height, name.c_str(),
                               glfwGetPrimaryMonitor(), NULL);
    width_ = mode->width;
    height_ = mode->height;
  } else {
    window_ = glfwCreateWindow(width_px, height_px, name.c_str(), NULL, NULL);
    width_ = width_px;
    height_ = height_px;
  }
  if (window_ == NULL) {
    forma::log::error("Failed to open window \"%s\"", name.c_str());
  }
  window::make_context_current(window_);
  window::init_glad();
}

forma::Window::~Window() {
  if (window_ != NULL) {
    glfwDestroyWindow(window_);
    window_ = NULL;
  }
}

void forma::Window::set_window_should_close(bool val) {
  should_close = val;
  glfwSetWindowShouldClose(window_, val);
}

bool forma::Window::window_should_close() {
  return glfwWindowShouldClose(window_);
}

void forma::Window::update() {
  window::make_context_current(window_);
  glfwSwapBuffers(window_);
  glfwPollEvents();
  glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
