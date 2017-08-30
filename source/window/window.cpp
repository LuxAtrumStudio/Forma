#include "window/window.hpp"

#include <memory>

#include "forma_core.hpp"
#include "gl.hpp"
#include "log/log.hpp"

#include "window/callback.hpp"

bool forma::window::Window::CreateWindow() { return GenerateWindow(); }

bool forma::window::Window::DestroyWindow() { return TerminateWindow(); }

void forma::window::Window::SetShouldClose(bool close) {
  should_close_ = close;
}

bool forma::window::Window::ShouldClose() { return should_close_; }

void forma::window::Window::MakeCurrent() {
  if (window_ != NULL && *window_ != NULL) {
    glfwMakeContextCurrent(*window_);
  }
}

void forma::window::Window::SetViewPort() {
  if (window_ != NULL && *window_ != NULL) {
    int fb_w = 0, fb_h = 0;
    glfwGetFramebufferSize(*window_, &fb_w, &fb_h);
    glViewport(0, 0, fb_w, fb_h);
  }
}

void forma::window::Window::Display() {
  if (window_ != NULL && *window_ != NULL) {
    if (glfwGetCurrentContext() != *window_) {
      MakeCurrent();
    }
    glfwSwapBuffers(*window_);
  }
}

void forma::window::Window::Clear() { glClear(GL_COLOR_BUFFER_BIT); }

bool forma::window::Window::GenerateWindow() {
  bool good = false;
  if (window_ != NULL) {
    log::Log(log::WARNING, "Window already exists",
             "forma::window::Window::GenerateWindow");
    good = true;
  } else {
    window_ = std::make_shared<GLFWwindow*>(
        glfwCreateWindow(size_[0], size_[1], name_, NULL, NULL));
    if (window_ == NULL || *window_ == NULL) {
      log::Log(log::ERROR, "Failed to generate window \"%s\"",
               "forma::window::Window::GenerateWindow", name_);
    } else {
      glfwSetFramebufferSizeCallback(*window_, FramebufferSizeCallback);
    }
  }
  return good;
}

bool forma::window::Window::TerminateWindow() {
  bool good = false;
  if (window_ != NULL && *window_ != NULL) {
    glfwDestroyWindow(*window_);
    good = true;
  }
  window_ = NULL;
  return good;
}
