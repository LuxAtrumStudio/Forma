#include <pessum.h>
#include <iostream>
#include "forma_files/forma_headers.hpp"
#include "forma_files/gl_headers.hpp"
#include <math.h>


void Close(std::shared_ptr<GLFWwindow*> win) {
  glfwSetWindowShouldClose(*win, GL_TRUE);
}

void PessumLogHandle(std::pair<int, std::string> entry) {
  if (entry.first == pessum::ERROR) {
    system("setterm -fore red");
  } else if (entry.first == pessum::WARNING) {
    system("setterm -fore yellow");
  } else if (entry.first == pessum::TRACE) {
    system("setterm -fore blue");
  } else if (entry.first == pessum::DEBUG) {
    system("setterm -fore magenta");
  } else if (entry.first == pessum::SUCCESS) {
    system("setterm -fore green");
  } else if (entry.first == pessum::DATA) {
    system("setterm -fore cyan");
  } else if (entry.first == pessum::INFO){
    system("setterm -fore white");
  }
  std::cout << entry.second << "\n";
  system("setterm -default");
}

int main(int argc, char const* argv[]) {
  pessum::SetLogHandle(PessumLogHandle);
  forma::InitForma();
  forma::Window win("Forma", 500, 500);
  win.SetKeyAction(int('Q'), 24, GLFW_PRESS, 0, Close);
  forma::Shader shade;
  shade.AddShader(forma::FORMA_VERTEX_SHADER, "forma_resources/vs.glsl");
  shade.AddShader(forma::FORMA_FRAGMENT_SHADER, "forma_resources/fs.glsl");
  shade.CreateProgram();
  forma::Object obj;
  obj.SetShaderProgram(shade);
  //obj.SetVertices({-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0});
  obj.SetVertices({0.5, 0.5, 0.0, 0.5, -0.5, 0.0, -0.5, -0.5, 0.0, -0.5, 0.5, 0.0});
  obj.SetIndices({0,1,3,1,2,3});
  obj.CreateObject();
  forma::Object obj_2;
  obj_2.SetShaderProgram(shade);
  obj_2.SetVertices({1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0});
  obj_2.SetIndices({0,1,3,1,2,3});
  obj_2.CreateObject();
  while (win.ShouldClose() == false) {
    float time = glfwGetTime();
    float green = (sin(time) / 2) + 0.5;
    shade.Uniform("our_color", forma::FORMA_FLOAT, 4, 0.0, green, 0.0, 1.0);
    glfwPollEvents();
    forma::HandleKey(win);
    obj.Display();
    obj_2.Display();
    win.Display();
  }
  win.DeleteWindow();
  forma::TermForma();
  pessum::SaveLog("out.log");
  return 0;
}
