// #include <GLFW/glfw3.h>
#include <forma/forma.hpp>

static void update_loop(float) {
  // forma::clear_background(forma::WHITE);
}

int main(void) {
  forma::initalize_logger(true);
  if (!forma::create_window(640, 480, "Hello world")) {
    return -1;
  }
  forma::run(update_loop);
  forma::close_window();
  return 0;
}
