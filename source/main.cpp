#include "forma.hpp"

int main(int argc, char *argv[])
{
  forma::InitForma();
  forma::video::Window win("Forma");
  while(!win.ShouldClose()){
    forma::input::PollEvents();
    win.HandleEvents();
  }
  win.Destroy();
  forma::TermForma();
  /* CODE */
  return 0;
}
