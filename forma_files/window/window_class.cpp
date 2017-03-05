#include <pessum.h>
#include "../framework/framework_headers.hpp"
#include "../gl_headers.hpp"
#include "../types/type_headers.hpp"
#include "window_class.hpp"

forma::window::Window::Window() { window_presets.fill(-1); }

forma::window::Window::Window(const Window& copy_window) {
  gl_window = copy_window.gl_window;
  window_size = copy_window.window_size;
  window_presets = copy_window.window_presets;
  clear_color = copy_window.clear_color;
}

forma::window::Window::~Window() { gl_window = nullptr; }

void forma::window::Window::WindowPreset(int preset, int setting) {
  window_presets.at(preset) = setting;
}

void forma::window::Window::CreateWindow(int width, int height,
                                         std::string name) {
  ReadPresets();
  gl_window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
  if (gl_window == nullptr) {
    pessum::logging::Log("error", "Failed to create GlFW window",
                         "forma/window/window_class/CreateWindow");
    glfwTerminate();
  }
  glfwMakeContextCurrent(gl_window);
  std::pair<int, int> fb = GetFrameBufferSize();
  framework::SetViewPort(fb.first, fb.second);
  window_size = std::make_pair(width, height);
  Clear();
}

void forma::window::Window::DeleteWindow() {
  if (gl_window != nullptr) {
    glfwDestroyWindow(gl_window);
    gl_window = nullptr;
  }
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

void forma::window::Window::Clear() {
  glClearColor(clear_color.first, clear_color.second, clear_color.third,
               clear_color.forth);
  glClear(GL_COLOR_BUFFER_BIT);
}

void forma::window::Window::SetClearColor(float red, float green, float blue,
                                          float alpha) {
  clear_color = make_quad(red, green, blue, alpha);
}

void forma::window::Window::ReadPresets() {
  for (int i = 0; i < 7; i++) {
    if (window_presets[i] != -1) {
      int target = 0, hint = 0;
      if (i == 0) {
        target = GLFW_RESIZABLE;
      } else if (i == 1) {
        target = GLFW_VISIBLE;
      } else if (i == 2) {
        target = GLFW_DECORATED;
      } else if (i == 3) {
        target = GLFW_FOCUSED;
      } else if (i == 4) {
        target = GLFW_AUTO_ICONIFY;
      } else if (i == 5) {
        target = GLFW_FLOATING;
      } else if (i == 6) {
        target = GLFW_MAXIMIZED;
      }
      if (window_presets[i] == 0) {
        hint = GLFW_FALSE;
      } else if (window_presets[i] == 1) {
        hint = GLFW_TRUE;
      }
      glfwWindowHint(target, hint);
    }
  }
}
