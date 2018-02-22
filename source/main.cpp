#include "forma.hpp"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
  forma::log::SetLogHandle(forma::log::PrintCallback);
  forma::log::SetLogOption(forma::log::TIME_STAMP, true);
  forma::log::SetLogOption(forma::log::DATE_STAMP, true);
  forma::InitForma();

  forma::window::Window win;
  win.CreateWindow();
  win.SetKeyEvent(forma::input::KEY_Q, forma::window::ACTION_QUIT);
  win.SetKeyEvent(forma::input::KEY_ESCAPE, forma::window::ACTION_QUIT);
  win.SetClearColor({{0.2, 0.3, 0.3, 1.0}});

  forma::shader::Shader shad;
  shad.VertexShader("resources/shaders/vertex.glsl");
  shad.FragmentShader("resources/shaders/frag.glsl");
  shad.CompileShader();

  forma::entity::Entity ent;
  ent.SetVerticies(
      {1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, -1.0, 0.0});
  ent.SetIndices({0, 1, 3, 1, 2, 3});
  ent.SetShader(shad.GetPtr());
  ent.CompileEntity();

  forma::entity::Entity en;
  // en.SetVerticies(
  //     {0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 1.0, 0.0});
  en.SetVerticies(
      {0.5, 0.5, 0.0, 0.5, -0.5, 0.0, -0.5, -0.5, 0.0, -0.5, 0.5, 0.0});
  en.SetIndices({0, 1, 3, 1, 2, 3});
  en.SetShader(shad.GetPtr());
  en.SetDisplayMode(forma::entity::LINE_LOOP);
  en.CompileEntity();

  while (win.ShouldClose() == false) {
    win.ProcessEvents();
    win.Clear();

    // win.Display(&ent);
    win.Display(&en);

    win.Update();
    forma::input::PollEvents();
  }
  win.DestroyWindow();
  forma::TermForma();
  forma::log::SaveLog("out.log");
  return 0;
}
