#include <forma/forma.hpp>

#include "forma/shader.hpp"
#include "forma/window.hpp"

using namespace forma;

int main(void) {
  window::create({500, 500}, "PONG");
  shader::Shader obj;
  obj.compile_shader();
  obj.use();
  // graphics::set_clear(forma::RED);
  // Sprite p1;
  while (!window::should_close()) {
    window::update();
  }
  obj.destroy_shader();
  window::destroy();
  return 0;
}
