#include <pessum.h>
#include <iostream>
#include "forma_files/forma_headers.hpp"

#define FORMA_VERSION "0.0.0"

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
  while (win.ShouldClose() == false) {
    glfwPollEvents();
    win.Display();
  }
  win.DeleteWindow();
  pessum::SaveLog("out.log");
  return 0;
}
