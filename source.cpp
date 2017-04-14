#include <pessum.h>
#include <iostream>
#include "forma_files/forma_headers.hpp"
#include "forma_files/gl_headers.hpp"

#define FORMA_VERSION "0.0.0"

void Close(GLFWwindow* win) { glfwSetWindowShouldClose(win, GL_TRUE); }

void PessumLogHandle(std::pair<int, std::string> entry) {
  if (entry.first == pessum::ERROR) {
    system("setterm -fore red");
  } else if (entry.first == pessum::WARNING) {
    system("setterm -fore yellow");
  } else if (entry.first == pessum::TRACE) {
    system("setterm -fore blue");
  } else if (entry.first == pessum::DEBUG) {
    system("setterm -fore magenta");
  } else if (entry.first == pessum::SUCCESS) {
    system("setterm -fore green");
  } else if (entry.first == pessum::DATA) {
    system("setterm -fore cyan");
  }
  std::cout << entry.second << "\n";
  system("setterm -fore white");
}

int main(int argc, char const* argv[]) {
  pessum::SetLogHandle(PessumLogHandle);
  forma::Window win = forma::InitForma("Forma", 100, 100);
  win.SetKeyAction(GLFW_KEY_ESCAPE, 9, GLFW_PRESS, 0, Close);
  while (win.ShouldClose() == false) {
    glfwPollEvents();
    forma::HandleKey(win);
    win.Display();
  }
  win.DeleteWindow();
  forma::TermForma();
  pessum::SaveLog("out.log");
  return 0;
}
