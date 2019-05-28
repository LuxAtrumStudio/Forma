#include "forma.hpp"

int main(int argc, char* argv[]) {
  forma::init();
  {
    forma::Window win(500, 500, "forma.ex0");
    win.clear_color = {0.149, 0.196, 0.219, 1.0};
    while (!win.window_should_close()) {
      win.update();
    }
  }
  forma::terminate();
  return 0;
}
