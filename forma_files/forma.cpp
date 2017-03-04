#include "forma.hpp"
#include "window/window_headers.hpp"

void forma::FormaLoop() {
  while (window::AllClosed() == false) {
    glfwPollEvents();
    window::UpdateAll();
  }
}
