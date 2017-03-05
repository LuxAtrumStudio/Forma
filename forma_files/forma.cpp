#include "forma.hpp"
#include "object/object_headers.hpp"
#include "window/window_headers.hpp"

void forma::FormaLoop() {
  while (window::AllClosed() == false) {
    glfwPollEvents();
    object::DisplayAll();
    window::UpdateAll();
  }
}
