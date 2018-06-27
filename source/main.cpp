#include "forma.hpp"

int main(int argc, char *argv[])
{
  forma::InitForma();

  forma::video::Window win("Forma");

  forma::shader::Shader shad;
  shad.VertexShader("resources/shaders/vertex.glsl");
  shad.FragmentShader("resources/shaders/frag.glsl");
  shad.CompileShader();

  while(!win.ShouldClose()){
    win.HandleEvents();
    win.Clear(0.2, 0.3, 0.3, 1.0);
    win.Update();
    forma::input::PollEvents();
    forma::FpsCheck();
  }
  win.Destroy();
  forma::TermForma();
  /* CODE */
  return 0;
}
