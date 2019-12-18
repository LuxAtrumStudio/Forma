#include <forma/forma.hpp>

int main(void) {
  forma::window::create({500, 500}, "PONG");
  while (!forma::window::should_close()) {
    forma::window::update();
  }
  forma::window::destroy();
  return 0;
}
