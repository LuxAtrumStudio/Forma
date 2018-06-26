#include "forma.hpp"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
  forma::logging::SetDefaultLogger(forma::logging::CONSOLE |
                                   forma::logging::LOG_FILE);
  forma::InitForma();

  forma::window::Window win;
  win.CreateWindow();
  win.SetKeyEvent(forma::input::KEY_Q, forma::window::ACTION_QUIT);
  win.SetKeyEvent(forma::input::KEY_ESCAPE, forma::window::ACTION_QUIT);
  win.SetKeyEvent(forma::input::KEY_T, forma::window::ACTION_LOG);
  win.SetClearColor({{0.2, 0.3, 0.3, 1.0}});

  forma::shader::Shader shad;
  shad.VertexShader("resources/shaders/vertex.glsl");
  shad.FragmentShader("resources/shaders/frag.glsl");
  shad.CompileShader();

  forma::entity::Entity ent;
  ent.SetVerticies(
      {0.5, 0.5, 0.0, 0.5, -0.5, 0.0, -0.5, -0.5, 0.0, -0.5, 0.5, 0.0});
  // ent.SetVertexAttribute(
  //     "color", {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0}, 1,
  //     3);
  ent.SetVertexAttribute(
      "color", {1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0}, 1,
      3);
  ent.SetIndices({0, 1, 3, 1, 2, 3});
  ent.SetShader(shad.GetPtr());
  ent.CompileEntity();

  while (win.ShouldClose() == false) {
    win.ProcessEvents();
    win.Clear();
    std::array<int, 4> key = win.GetKey();
    if (key[0] != 0) {
      std::cout << "KEY: " << key[0] << ", " << key[1] << ", " << key[2] << ", "
                << key[3] << "\n";
    }

    win.Display(&ent);

    win.Update();
    forma::input::PollEvents();
  }
  win.DestroyWindow();
  forma::TermForma();
  return 0;
}
