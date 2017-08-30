#include "window/window.hpp"

#include <memory>

#include "forma_core.hpp"
#include "gl.hpp"
#include "input/input.hpp"
#include "input/key.hpp"
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

void forma::window::Window::SetKeyEvent(std::array<int, 4> key_info,
                                        unsigned int set_action) {
  key_action_[key_info] = set_action;
}

void forma::window::Window::SetKeyEvent(unsigned int key,
                                        unsigned int set_action) {
  key_action_[std::array<int, 4>{{(int)key, -1, -1, -1}}] = set_action;
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
      log::Log(log::TRACE, "Log call from \"%s\"",
               "forma::window::Window::RunAction", name_);
      break;
    case ACTION_QUIT:
      SetShouldClose(true);
      break;
  }
}
