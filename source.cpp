#include "forma_files/forma_headers.hpp"
#include "forma_files/gl_headers.hpp"
#include <pessum.h>

#define FORMA_VERSION "0.0.1"

int main(int argc, char const *argv[]) {
  pessum::InitializePessum(true, true);
  forma::framework::InitGlfw();
  forma::framework::GlfwVersion();
  forma::framework::GlfwProfile();
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  forma::window::Window win;
  std::string name = "Forma ";
  name.append(FORMA_VERSION);
  win.CreateWindow(500, 500, name);
  forma::framework::InitGlew();
  std::pair<int, int> fbs = win.GetFrameBufferSize();
  forma::framework::SetViewPort(fbs.first, fbs.second);
  while (!win.ShouldClose()) {
    glfwPollEvents();
    win.Update();
  }
  glfwTerminate();
  pessum::TerminatePessum();
  return 0;
}
