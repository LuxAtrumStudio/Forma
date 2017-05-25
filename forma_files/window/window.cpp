#include <pessum.h>
#include "../gl_headers.hpp"
#include "../input/input_headers.hpp"
#include "window.hpp"

forma::Window::Window() {}

forma::Window::Window(int width, int height) {
  if (ptr != NULL) {
    pessum::Log(pessum::WARNING, "Window not destroyed before initialization",
                "forma::Window::Window");
    DeleteWindow();
  }
  ptr = std::make_shared<GLFWwindow*>(
      glfwCreateWindow(width, height, "(null)", NULL, NULL));
  if (ptr == NULL) {
    pessum::Log(pessum::WARNING, "Failed to create GLFW window",
                "forma::Window::CreateWindow");
  } else {
    glfwMakeContextCurrent(*ptr);
    int fb_width, fb_height;
    glfwGetFramebufferSize(*ptr, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);
    glfwSetKeyCallback(*ptr, KeyCallback);
  }
}

forma::Window::Window(std::string name, int width, int height) {
  if (ptr != NULL) {
    pessum::Log(pessum::WARNING, "Window not destroyed before initialization",
                "forma::Window::Window");
    DeleteWindow();
  }
  ptr = std::make_shared<GLFWwindow*>(
      glfwCreateWindow(width, height, name.c_str(), NULL, NULL));
  if (ptr == NULL) {
    pessum::Log(pessum::WARNING, "Failed to create GLFW window",
                "forma::Window::CreateWindow");
  } else {
    glfwMakeContextCurrent(*ptr);
    int fb_width, fb_height;
    glfwGetFramebufferSize(*ptr, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);
    glfwSetKeyCallback(*ptr, KeyCallback);
  }
}

forma::Window::Window(const Window& copy) {
  ptr = copy.ptr;
  clear_color = copy.clear_color;
  key_actions = copy.key_actions;
}

forma::Window::~Window() {
  if (ptr.use_count() == 1) {
    glfwDestroyWindow(*ptr);
    ptr = NULL;
  }
  clear_color = {{0.0f, 0.0f, 0.0f, 1.0f}};
}

void forma::Window::Preset(int option, int setting) {
  glfwWindowHint(option, setting);
}

void forma::Window::CreateWindow(std::string name, int width, int height) {
  if (ptr != NULL) {
    pessum::Log(pessum::WARNING, "Window not destroyed before initialized",
                "forma::Window::CreateWindow");
    DeleteWindow();
  }
  ptr = std::make_shared<GLFWwindow*>(
      glfwCreateWindow(width, height, name.c_str(), NULL, NULL));
  if (ptr == NULL) {
    pessum::Log(pessum::WARNING, "Failed to create GLFW window",
                "forma::Window::CreateWindow");
  } else {
    glfwMakeContextCurrent(*ptr);
    int fb_width, fb_height;
    glfwGetFramebufferSize(*ptr, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);
    glfwSetKeyCallback(*ptr, KeyCallback);
  }
}

void forma::Window::DeleteWindow() {
  if (ptr != NULL) {
    if (ptr.use_count() == 1) {
      glfwDestroyWindow(*ptr);
    }
    ptr = NULL;
  } else {
    pessum::Log(pessum::WARNING, "Window already destroyed",
                "forma::Window::DeleteWindow");
    ptr = NULL;
  }
}

bool forma::Window::ShouldClose() {
  if (ptr != NULL) {
    if (glfwWindowShouldClose(*ptr) == GL_FALSE) {
      return (false);
    } else {
      return (true);
    }
  }
  return (true);
}

void forma::Window::MakeCurrent() {
  if (ptr != NULL) {
    glfwMakeContextCurrent(*ptr);
    int fb_width, fb_height;
    glfwGetFramebufferSize(*ptr, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);
  } else {
    pessum::Log(pessum::WARNING, "Window not initialized",
                "forma::Window::MakeCurrent");
  }
}

void forma::Window::Display() {
  if (ptr != NULL) {
    glfwSwapBuffers(*ptr);
  } else {
    pessum::Log(pessum::WARNING, "Window not initialized",
                "forma::Window::Display");
  }
}

void forma::Window::Clear() {
  if (ptr != NULL) {
    glClearColor(clear_color[0], clear_color[1], clear_color[2],
                 clear_color[3]);
    glClear(GL_COLOR_BUFFER_BIT);
  } else {
    pessum::Log(pessum::WARNING, "Window not initialized",
                "forma::Window::Clear");
  }
}

void forma::Window::KeyPress(
    std::tuple<GLFWwindow*, int, int, int, int> key_call) {
  if (ptr != NULL) {
    std::array<int, 4> key_def{{std::get<1>(key_call), std::get<2>(key_call),
                                std::get<3>(key_call), std::get<4>(key_call)}};
    // pessum::Log(pessum::DATA, "%i,%i,%i,%i", "KeyPress", key_def[0],
    // key_def[1],
    //             key_def[2], key_def[3]);
    std::map<std::array<int, 4>,
             void (*)(std::shared_ptr<GLFWwindow*>)>::iterator it;
    it = key_actions.find(key_def);
    if (it != key_actions.end()) {
      it->second(ptr);
    }
  } else {
    pessum::Log(pessum::WARNING, "Window not initialized",
                "forma::Window::KeyPress");
  }
}

void forma::Window::SetKeyAction(int key, int scan_code, int action, int mode,
                                 void (*func)(std::shared_ptr<GLFWwindow*>)) {
  key_actions[std::array<int, 4>{{key, scan_code, action, mode}}] = func;
}

void forma::Window::CloseWindow() {
  if (ptr != NULL) {
    glfwSetWindowShouldClose(*ptr, GL_TRUE);
  } else {
    pessum::Log(pessum::WARNING, "Window not initialized",
                "forma::Window::CloseWindow");
  }
}

std::shared_ptr<GLFWwindow*> forma::Window::operator()() { return (ptr); }
