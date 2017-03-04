#include "../gl_headers.hpp"
#include "window.hpp"
#include <pessum.h>

forma::window::Window::Window() { window_presets.fill(0); }

forma::window::Window::~Window() {}

void forma::window::Window::WindowPreset(int preset, int setting) {
  window_presets.at(preset) = setting;
}

void forma::window::Window::CreateWindow(int width, int height,
                                         std::string name) {
  gl_window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
  if (gl_window == nullptr) {
    pessum::logging::Log("error", "Failed to create GlFW window",
                         "forma/window/window/CreateWindow");
    glfwTerminate();
  }
  glfwMakeContextCurrent(gl_window);
  window_size = std::make_pair(width, height);
}

bool forma::window::Window::ShouldClose() {
  if (glfwWindowShouldClose(gl_window) == GL_FALSE) {
    return (false);
  } else {
    return (true);
  }
}

std::pair<int, int> forma::window::Window::GetSize() { return (window_size); }

std::pair<int, int> forma::window::Window::GetFrameBufferSize() {
  int width, height;
  glfwGetFramebufferSize(gl_window, &width, &height);
  return (std::make_pair(width, height));
}

void forma::window::Window::Update() { glfwSwapBuffers(gl_window); }
