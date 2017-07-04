#include "window.hpp"

#include <pessum/pessum.hpp>

#include "../gl_headers.hpp"

forma::Window::Window() { GenorateWindow(); }

forma::Window::Window(unsigned int state) {
  ReadState(state);
  GenorateWindow();
}

forma::Window::Window(int width, int height, unsigned int state) {
  ReadState(state);
  GenorateWindow();
}

forma::Window::Window(const Window& copy) { ptr = copy.ptr; }

forma::Window::~Window() {
  if (ptr.use_count() == 1) {
    glfwDestroyWindow(*ptr);
  }
  ptr = NULL;
}

void forma::Window::GenorateWindow() {
  if (ptr != NULL) {
    pessum::Log(pessum::WARNING, "Window already initialized",
                "forma::Window::GenorateWindow()");
  } else {
    ptr = std::make_shared<GLFWwindow*>(
        glfwCreateWindow(size[0], size[1], name.c_str(), NULL, NULL));
    if (ptr == NULL) {
      pessum::Log(pessum::WARNING, "Failed to create window %s",
                  "forma::Window::GenorateWindow()", name.c_str());
    }
  }
}

void forma::Window::ReadState(unsigned int state) {
  if ((state & RESIZABLE) != 0) {
  }
  if ((state & VISIBLE) != 0) {
  }
  if ((state & DECORATED) != 0) {
  }
  if ((state & FOCUSED) != 0) {
  }
  if ((state & AUTO_ICONIFY) != 0) {
  }
  if ((state & FLOATING) != 0) {
  }
  if ((state & MAXIMIZED) != 0) {
  }
  if ((state & FULLSCREEN) != 0) {
  }
  if ((state & BORDERLESS_FULLSCREEN) != 0) {
  }
}
