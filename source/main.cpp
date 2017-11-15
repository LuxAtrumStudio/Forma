#include "forma.hpp"

#include <iostream>

void LogCallback(std::string entry) { std::cout << entry << "\n"; }

void ACallBack(std::shared_ptr<GLFWwindow*> win) {
  forma::log::Log(forma::log::INFO, "Pressed A");
}

int main(int argc, char const* argv[]) {
  forma::log::SetLogHandle(LogCallback);
  forma::log::SetLogOption(forma::log::TIME_STAMP, true);
  forma::log::SetLogOption(forma::log::DATE_STAMP, true);
  forma::InitForma();

  forma::window::Window win;
  win.CreateWindow();
  win.SetKeyEvent(forma::input::KEY_ESCAPE, forma::window::ACTION_QUIT);

  forma::shader::Shader shade;
  shade.VertexShader("resources/shaders/vertex.glsl");
  shade.FragmentShader("resources/shaders/frag.glsl");
  shade.CompileShader();
  shade.Use();

  forma::entity::Entity ent;
  ent.SetShader(shade.GetPtr());

  while (win.ShouldClose() == false) {
    win.ProcessEvents();

    win.Clear();
    // win.Display(&ent);
    win.Update();

    forma::input::PollEvents();
  }
  win.DestroyWindow();
  forma::TermForma();
  forma::log::SaveLog("out.log");
  return 0;
}
