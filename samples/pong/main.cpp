#include <forma/forma.hpp>
#include "forma/window.hpp"

using namespace forma;

int main(void) {
  window::create({500, 500}, "PONG");
  // graphics::set_clear(forma::RED);
  while (!window::should_close()) {
    window::update();
  }
  window::destroy();
  return 0;
}
