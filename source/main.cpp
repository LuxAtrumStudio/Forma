#include "forma.hpp"

#include <iostream>

void LogCallback(std::string entry) { std::cout << entry << "\n"; }

int main(int argc, char const* argv[]) {
  forma::log::SetLogHandle(LogCallback);
  forma::log::SetLogOption(forma::log::TIME_STAMP, true);
  forma::InitForma();
  forma::window::Window win;
  win.CreateWindow();
  win.SetKeyEvent(forma::input::KEY_ESCAPE, forma::window::ACTION_QUIT);
  win.SetKeyEvent(forma::input::KEY_Q, forma::window::ACTION_LOG);
  while (win.ShouldClose() == false) {
    win.ProcessEvents();

    win.Clear();
    win.Display();

    forma::input::PollEvents();
  }
  win.DestroyWindow();
  forma::TermForma();
  forma::log::SaveLog("out.log");
  return 0;
}
