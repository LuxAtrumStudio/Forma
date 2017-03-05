#include <pessum.h>
#include "forma_files/forma_headers.hpp"
#include "forma_files/gl_headers.hpp"

#define FORMA_VERSION "0.0.2"

int main(int argc, char const* argv[]) {
  pessum::InitializePessum(true, true);
  forma::framework::InitGlfw();
  std::string name = "Forma ";
  name.append(FORMA_VERSION);
  forma::window::CreateWindow(500, 500, name);
  forma::framework::InitGlew();
  forma::object::CreateShader("resources/shaders/vertex_shader.glsl",
                              "resources/shaders/fragment_shader.glsl");
  int obj = forma::object::CreateObject();
  forma::object::objects[obj].SetVertices({
      0.5f, 0.5f, 0.0f,    // Top Right
      0.5f, -0.5f, 0.0f,   // Bottom Right
      -0.5f, -0.5f, 0.0f,  // Bottom Left
      -0.5f, 0.5f, 0.0f    // Top Left
  });
  forma::object::objects[obj].SetIndices({0, 1, 3, 1, 2, 3});
  forma::object::objects[obj].CreateObject();
  forma::framework::PolygonMode(2, 1);
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  forma::FormaLoop();
  glfwTerminate();
  pessum::TerminatePessum();
  return 0;
}
