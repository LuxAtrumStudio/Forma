#include <pessum.h>
#include "../gl_headers.hpp"
#include "window.hpp"

void forma::Window::Preset(int option, int setting) {}

void forma::Window::CreateWindow(int width, int height, std::string name) {
  if (ptr != NULL) {
    pessum::Log(pessum::WARNING, "Window not destroyed before initialized",
                "forma/Window/CreateWindow");
    DeleteWindow();
  }
  ptr = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
  if (ptr == NULL) {
    pessum::Log(pessum::WARNING, "Failed to create GLFW window",
                "forma/Window/CreateWindow");
  } else {
    glfwMakeContextCurrent(ptr);
    int fb_width, fb_height;
    glfwGetFramebufferSize(ptr, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);
  }
}

void forma::Window::DeleteWindow() {
  if (ptr != NULL) {
    glfwDestroyWindow(ptr);
    ptr = NULL;
  } else {
    pessum::Log(pessum::WARNING, "Window already destroyed",
                "forma/Window/DeleteWindow");
    ptr = NULL;
  }
}

bool forma::Window::ShouldClose() {
  if (ptr != NULL) {
    if (glfwWindowShouldClose(ptr) == GL_FALSE) {
      return (false);
    } else {
      return (true);
    }
  }
  return (true);
}

void forma::Window::Display() {
  if (ptr != NULL) {
    glfwSwapBuffers(ptr);
  } else {
    pessum::Log(pessum::WARNING, "Window not initialized",
                "forma/Window/Display");
  }
}

void forma::Window::Clear() {
  if (ptr != NULL) {
    glClearColor(clear_color[0], clear_color[1], clear_color[2],
                 clear_color[3]);
    glClear(GL_COLOR_BUFFER_BIT);
  } else {
    pessum::Log(pessum::WARNING, "Window not initialized",
                "forma/Window/Clear");
  }
}
