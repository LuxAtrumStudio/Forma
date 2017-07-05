#include <iostream>
#include <pessum/pessum.hpp>

#include "forma.hpp"
#include "gl_headers.hpp"

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
  } else if (entry.first == pessum::INFO) {
    system("setterm -fore white");
  }
  std::cout << entry.second << "\n";
  system("setterm -default");
}

int main(int argc, const char* argv[]) {
  pessum::SetLogHandle(PessumLogHandle);
  forma::InitForma();
  forma::window::Window win;
  win.SetKeyAction(std::array<int, 4>{{GLFW_KEY_ESCAPE, -1, -1, -1}},
                   forma::window::QUIT);
  forma::window::Window win_2;
  win_2.SetKeyAction(std::array<int, 4>{{GLFW_KEY_Q, -1, -1, -1}},
                     forma::window::QUIT);
  while (win.ShouldClose() == false && win_2.ShouldClose() == false) {
    glfwPollEvents();
    forma::input::HandleKeyCall(win);
    forma::input::HandleKeyCall(win_2);
    win.Update();
    win_2.Update();
  }
  win.Delete();
  win_2.Delete();
  forma::TermForma();
  pessum::SaveLog("out.log");
  return 0;
}
