#include "forma.hpp"

int main(int argc, char const* argv[]) {
  forma::log::SetLogOption(forma::log::TIME_STAMP, true);
  forma::log::SetLogOption(forma::log::DATE_STAMP, true);
  forma::InitForma();
  forma::window::Window win;
  win.CreateWindow();
  while (win.ShouldClose() == false) {
    win.Clear();
    win.Display();
  }
  win.DestroyWindow();
  forma::TermForma();
  forma::log::SaveLog("out.log");
  return 0;
}
