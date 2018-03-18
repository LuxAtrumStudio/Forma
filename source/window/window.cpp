#include "window/window.hpp"

#include <memory>

#include "forma_core.hpp"
#include "gl.hpp"
#include "input/input.hpp"
#include "input/key.hpp"
#include "log/logger.hpp"
#include "window/callback.hpp"

forma::window::Window::Window() {}

forma::window::Window::Window(const Window& copy) {
  should_close_ = copy.should_close_;
  name_ = copy.name_;
  size_ = copy.size_;
  clear_color_ = copy.clear_color_;
  key_action_ = copy.key_action_;
  key_function_ = copy.key_function_;
  window_ = copy.window_;
}

forma::window::Window::~Window() { TerminateWindow(); }

bool forma::window::Window::CreateWindow() { return GenerateWindow(); }

bool forma::window::Window::DestroyWindow() { return TerminateWindow(); }

void forma::window::Window::SetShouldClose(bool close) {
  should_close_ = close;
}

bool forma::window::Window::ShouldClose() {
  if (glfwWindowShouldClose(*window_) == true) {
    return true;
  }
  return should_close_;
}

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

void forma::window::Window::SetClearColor(std::array<float, 4> color) {
  clear_color_ = color;
}

void forma::window::Window::Update() {
  if (window_ != NULL && *window_ != NULL) {
    if (glfwGetCurrentContext() != *window_) {
      MakeCurrent();
    }
    glfwSwapBuffers(*window_);
  }
}

void forma::window::Window::Clear() {
  glClearColor(clear_color_[0], clear_color_[1], clear_color_[2],
               clear_color_[3]);
  glClear(GL_COLOR_BUFFER_BIT);
}

void forma::window::Window::Display(entity::Entity* ptr) {
  if (window_ != NULL && *window_ != NULL) {
    if (glfwGetCurrentContext() != *window_) {
      MakeCurrent();
    }
    ptr->Display();
  }
}

void forma::window::Window::SetKeyEvent(std::array<int, 4> key_info,
                                        unsigned int set_action) {
  key_action_[key_info] = set_action;
}

void forma::window::Window::SetKeyEvent(unsigned int key,
                                        unsigned int set_action) {
  key_action_[std::array<int, 4>{{static_cast<int>(key), -1, -1, -1}}] =
      set_action;
}

void forma::window::Window::SetKeyEvent(
    std::array<int, 4> key_info,
    std::function<void(std::shared_ptr<GLFWwindow*>)> func) {
  key_function_[key_info] = func;
}

void forma::window::Window::SetKeyEvent(
    unsigned int key, std::function<void(std::shared_ptr<GLFWwindow*>)> func) {
  key_function_[std::array<int, 4>{{static_cast<int>(key), -1, -1, -1}}] = func;
}

void forma::window::Window::ProcessEvents() {
  std::vector<std::array<int, 4>> key_inputs = input::GetKeyData(*window_);
  for (std::vector<std::array<int, 4>>::iterator it = key_inputs.begin();
       it != key_inputs.end(); ++it) {
    for (std::map<std::array<int, 4>, unsigned int>::iterator action =
             key_action_.begin();
         action != key_action_.end(); ++action) {
      if ((action->first[0] == (*it)[0] || action->first[0] == -1) &&
          (action->first[1] == (*it)[1] || action->first[1] == -1) &&
          (action->first[2] == (*it)[2] || action->first[2] == -1) &&
          (action->first[3] == (*it)[3] || action->first[3] == -1)) {
        RunAction(action->second);
      }
    }
    for (std::map<std::array<int, 4>,
                  std::function<void(std::shared_ptr<GLFWwindow*>)>>::iterator
             action = key_function_.begin();
         action != key_function_.end(); ++action) {
      if ((action->first[0] == (*it)[0] || action->first[0] == -1) &&
          (action->first[1] == (*it)[1] || action->first[1] == -1) &&
          (action->first[2] == (*it)[2] || action->first[2] == -1) &&
          (action->first[3] == (*it)[3] || action->first[3] == -1)) {
        action->second(window_);
      }
    }
  }
}

GLFWwindow* forma::window::Window::GetPointer() {
  if (window_ != NULL) {
    return *window_;
  }
}

bool forma::window::Window::GenerateWindow() {
  bool good = false;
  if (window_ != NULL) {
    logging::Warning("window/window.cpp",
                     "forma::window::Window::GenerateWindow()",
                     "Window already exists");
    good = true;
  } else {
    window_ = std::make_shared<GLFWwindow*>(
        glfwCreateWindow(size_[0], size_[1], name_, NULL, NULL));
    if (window_ == NULL || *window_ == NULL) {
      logging::Error("window/window.cpp",
                     "forma::window::Window::GenerateWindow()",
                     "Failed to generate window \"%s\"", name_);
    } else {
      glfwMakeContextCurrent(*window_);
      glfwSetFramebufferSizeCallback(*window_, FramebufferSizeCallback);
      glfwSetKeyCallback(*window_, input::KeyCallBack);
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

void forma::window::Window::RunAction(unsigned int action) {
  switch (action) {
    case ACTION_LOG:
      logging::Trace("window/window.cpp",
                     "forma::window::Window::RunAction(unsigned int)",
                     "Log call from \"%s\"", name_);
      break;
    case ACTION_QUIT:
      SetShouldClose(true);
      break;
  }
}
