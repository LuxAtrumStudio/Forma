#include <forma/forma.hpp>

#include "forma/window.hpp"

using namespace forma;

int main(void) {
  init(500, 500, "PONG");
  graphics::set_clear(forma::RED);
  Sprite p1;
  while (!should_close()) {
    update();
  }
  term();
  return 0;
}
