#include "window.hpp"

#include <algorithm>
#include <array>

#include <pessum/pessum.hpp>

#include "../gl_headers.hpp"
#include "../input/input.hpp"
#include "window_external.hpp"

forma::window::Window::Window() {
  GenorateWindow();
  MakeCurrent();
}

forma::window::Window::Window(unsigned int state) {
  ReadState(state);
  GenorateWindow();
  MakeCurrent();
}

forma::window::Window::Window(int width, int height, unsigned int state) {
  ReadState(state);
  GenorateWindow();
  MakeCurrent();
}

forma::window::Window::Window(const Window& copy) {
  ptr = copy.ptr;
  key_actions = copy.key_actions;
  size = copy.size;
  name = copy.name;
  full_screen = copy.full_screen;
}

forma::window::Window::~Window() {
  if (ptr.use_count() == 1 && ptr != NULL) {
    glfwDestroyWindow(*ptr);
  }
  ptr = NULL;
}

void forma::window::Window::Delete() {
  if (ptr.use_count() == 1 && ptr != NULL) {
    glfwDestroyWindow(*ptr);
  }
  ptr = NULL;
}

void forma::window::Window::Close() {
  if (ptr != NULL) {
    glfwSetWindowShouldClose(*ptr, true);
  }
}

void forma::window::Window::MakeCurrent() {
  if (ptr != NULL) {
    glfwMakeContextCurrent(*ptr);
  }
}

void forma::window::Window::SetViewport() {
  if (ptr != NULL) {
    int fb_w = 0, fb_h = 0;
    glfwGetFramebufferSize(*ptr, &fb_w, &fb_h);
    glViewport(0, 0, fb_w, fb_h);
  }
}

void forma::window::Window::Update() {
  if (ptr != NULL) {
    glfwSwapBuffers(*ptr);
  }
}

void forma::window::Window::SetKeyAction(
    std::array<int, 4> key_info, void (*func)(std::shared_ptr<GLFWwindow*>)) {
  // std::vector<std::tuple<std::array<int, 4>, int,
  // void (*)(std::shared_ptr<GLFWwindow*>) >> ::iterator it =
  //   std::find(key_actions.begin(), key_actions.end());
  key_actions.push_back(std::make_tuple(key_info, -1, func));
}

void forma::window::Window::SetKeyAction(std::array<int, 4> key_info,
                                         int action) {
  void (*null)(std::shared_ptr<GLFWwindow*>) = NULL;
  key_actions.push_back(std::make_tuple(key_info, action, null));
}

void forma::window::Window::KeyCallback(std::array<int, 4> key_info) {
  for (int i = 0; i < key_actions.size(); i++) {
    bool match = true;
    for (int j = 0; j < 4 && match == true; j++) {
      if (key_info[j] != std::get<0>(key_actions[i])[j] &&
          std::get<0>(key_actions[i])[j] != -1) {
        match = false;
      }
    }
    if (match == true) {
      if (std::get<1>(key_actions[i]) != -1) {
        int action = std::get<1>(key_actions[i]);
        if (action == QUIT) {
          Close();
        }
      }
      if (std::get<2>(key_actions[i]) != NULL) {
        std::get<2>(key_actions[i])(ptr);
      }
    }
  }
}

std::shared_ptr<GLFWwindow*> forma::window::Window::operator()() {
  return (ptr);
}

void forma::window::Window::GenorateWindow() {
  if (ptr != NULL) {
    pessum::Log(pessum::WARNING, "Window already initialized",
                "forma::window::Window::GenorateWindow()");
  } else {
    if (full_screen == 0) {
      ptr = std::make_shared<GLFWwindow*>(
          glfwCreateWindow(size[0], size[1], name.c_str(), NULL, NULL));
    } else if (full_screen == DEFAULT) {
      ptr = std::make_shared<GLFWwindow*>(
          glfwCreateWindow(size[0], size[1], name.c_str(), NULL, NULL));
    }
    if (ptr == NULL) {
      pessum::Log(pessum::WARNING, "Failed to create window %s",
                  "forma::window::Window::GenorateWindow()", name.c_str());
    } else {
      glfwSetFramebufferSizeCallback(*ptr, FramebufferSizeCallback);
      glfwSetKeyCallback(*ptr, input::KeyCallback);
    }
  }
}

void forma::window::Window::ReadState(unsigned int state) {
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
