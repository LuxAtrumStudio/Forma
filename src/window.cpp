#include "window.hpp"

#include <string>

#include <GLFW/glfw3.h>

#include "logger.hpp"

forma::Window::Window() {}
forma::Window::Window(const unsigned& width_px, const unsigned& height_px,
                      const std::string& name, bool full_screen) {
  name_ = name;
  if (full_screen) {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    window_ = glfwCreateWindow(mode->width, mode->height, name.c_str(),
                               glfwGetPrimaryMonitor(), NULL);
    width_ = mode->width;
    height_ = mode->height;
  }else{
    window_ = glfwCreateWindow(width_px, height_px, name.c_str(), NULL, NULL);
    width_ = width_px;
    height_ = height_px;
  }
  if(window_ == NULL){
    forma::log::error("Failed to open window \"%s\"", name.c_str());
  }
}

forma::Window::~Window(){
  if(window_ != NULL){
    glfwDestroyWindow(window_);
    window_ = NULL;
  }
}
