#include <pessum.h>
#include "forma_files/forma_headers.hpp"
#include "forma_files/gl_headers.hpp"

#define FORMA_VERSION "0.0.1"

int main(int argc, char const* argv[]) {
  pessum::InitializePessum(true, true);
  forma::framework::InitGlfw();
  std::string name = "Forma ";
  name.append(FORMA_VERSION);
  forma::window::CreateWindow(500, 500, name);
  forma::framework::InitGlew();
  forma::FormaLoop();
  glfwTerminate();
  pessum::TerminatePessum();
  return 0;
}
