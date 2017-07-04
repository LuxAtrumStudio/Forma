#include "window.hpp"

#include <pessum/pessum.hpp>

#include "../gl_headers.hpp"

forma::Window::Window() {
  GenorateWindow();
  MakeCurrent();
}

forma::Window::Window(unsigned int state) {
  ReadState(state);
  GenorateWindow();
  MakeCurrent();
}

forma::Window::Window(int width, int height, unsigned int state) {
  ReadState(state);
  GenorateWindow();
  MakeCurrent();
}

forma::Window::Window(const Window& copy) { ptr = copy.ptr; }

forma::Window::~Window() {
  if (ptr.use_count() == 1 && ptr != NULL) {
    glfwDestroyWindow(*ptr);
  }
  ptr = NULL;
}

void forma::Window::Delete() {
  if (ptr.use_count() == 1 && ptr != NULL) {
    glfwDestroyWindow(*ptr);
  }
  ptr = NULL;
}

void forma::Window::MakeCurrent() {
  if (ptr != NULL) {
    glfwMakeContextCurrent(*ptr);
  }
}

void forma::Window::SetViewport() {
  if (ptr != NULL) {
    int fb_w = 0, fb_h = 0;
    glfwGetFramebufferSize(*ptr, &fb_w, &fb_h);
    glViewport(0, 0, fb_w, fb_h);
  }
}

void forma::Window::Update() {
  if (ptr != NULL) {
    glfwSwapBuffers(*ptr);
  }
}

std::shared_ptr<GLFWwindow*> forma::Window::operator()() { return (ptr); }

void forma::Window::GenorateWindow() {
  if (ptr != NULL) {
    pessum::Log(pessum::WARNING, "Window already initialized",
                "forma::Window::GenorateWindow()");
  } else {
    if (full_screen == 0) {
      ptr = std::make_shared<GLFWwindow*>(
          glfwCreateWindow(size[0], size[1], name.c_str(), NULL, NULL));
    } else if (full_screen == DEFAULT) {
      ptr = std::make_shared<GLFWwindow*>(glfwCreateWindow(
          size[0], size[1], name.c_str(), glfwGetPrimaryMonitor(), NULL));
    }
    if (ptr == NULL) {
      pessum::Log(pessum::WARNING, "Failed to create window %s",
                  "forma::Window::GenorateWindow()", name.c_str());
    }
  }
}

void forma::Window::ReadState(unsigned int state) {
  if ((state & RESIZABLE) != 0) {
    GlfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  } else {
    GlfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  }
  if ((state & VISIBLE) != 0) {
    GlfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
  } else {
    GlfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  }
  if ((state & DECORATED) != 0) {
    GlfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
  } else {
    GlfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
  }
  if ((state & FOCUSED) != 0) {
    GlfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
  } else {
    GlfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
  }
  if ((state & AUTO_ICONIFY) != 0) {
    GlfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);
  } else {
    GlfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
  }
  if ((state & FLOATING) != 0) {
    GlfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
  } else {
    GlfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
  }
  if ((state & MAXIMIZED) != 0) {
    GlfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
  } else {
    GlfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
  }
  if ((state & FULLSCREEN) != 0) {
    full_screen = DEFAULT;
  }
  if ((state & BORDERLESS_FULLSCREEN) != 0) {
    full_screen = BORDERLESS;
  }
}
