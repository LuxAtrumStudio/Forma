#include "video/window.hpp"

#include <memory>
#include <string>

#include <estl/logger.hpp>

#include "core.hpp"
#include "gl.hpp"
#include "input/key.hpp"
#include "video/callback.hpp"

forma::video::Window::Window()
    : name_("Forma"),
      width_(500),
      height_(500),
      should_close_(false),
      ptr_(nullptr) {}
forma::video::Window::Window(std::string name)
    : name_(name),
      width_(500),
      height_(500),
      should_close_(false),
      ptr_(nullptr) {
  Create();
}
forma::video::Window::Window(std::string name, uint16_t width, uint16_t height)
    : name_(name),
      width_(width),
      height_(height),
      should_close_(false),
      ptr_(nullptr) {
  Create();
}
forma::video::Window::~Window() { Destroy(); }

bool forma::video::Window::Create() {
  if (ptr_ != nullptr && *ptr_ != nullptr) {
    estl::logger::Warning("Window \"%s\" already exists", name_.c_str());
    Destroy();
  }
  ptr_ = std::make_unique<GLFWwindow*>(
      glfwCreateWindow(width_, height_, name_.c_str(), nullptr, nullptr));
  if (ptr_ == nullptr || *ptr_ == nullptr) {
    estl::logger::Error("Failed to generate window \"%s\"", name_.c_str());
    return false;
  } else {
    glfwMakeContextCurrent(*ptr_);
    glfwSetFramebufferSizeCallback(*ptr_, FramebufferSizeCallback);
    glfwSetKeyCallback(*ptr_, input::KeyCallback);
    if (!IsInitGlad()) {
      InitGlad();
    }
    return true;
  }
}
bool forma::video::Window::Destroy() {
  if (ptr_ != nullptr && *ptr_ != nullptr) {
    glfwDestroyWindow(*ptr_);
    ptr_ = nullptr;
    return true;
  } else {
    return false;
  }
}

void forma::video::Window::SetShouldClose(bool close){
  should_close_ = close;
}

bool forma::video::Window::ShouldClose() const {
  if(glfwWindowShouldClose(*ptr_)){
    return true;
  }
  return should_close_;
}

void forma::video::Window::MakeCurrent() const{
  if(ptr_ != nullptr && *ptr_ != nullptr){
    glfwMakeContextCurrent(*ptr_);
  }
}

void forma::video::Window::HandleEvents(){
}

void forma::video::Window::Update() const {
  if(ptr_ != nullptr && *ptr_ != nullptr){
    glfwSwapBuffers(*ptr_);
  }
}

void forma::video::Window::Clear(float r, float g, float b, float a) const {
  glClearColor(r, g, b, a);
  glClear(GL_COLOR_BUFFER_BIT);
}

std::string forma::video::Window::GetName() const{
  return name_;
}
uint16_t forma::video::Window::GetWidth() const{
  return width_;
}
uint16_t forma::video::Window::GetHeight() const{
  return height_;
}

