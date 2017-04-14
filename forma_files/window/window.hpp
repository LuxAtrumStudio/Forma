#ifndef FORMA_WINDOW_HPP
#define FORMA_WINDOW_HPP
#include <array>
#include <map>
#include <string>
#include <tuple>
#include "../gl_headers.hpp"
namespace forma {
  class Window {
   public:
    void Preset(int option, int setting);
    void CreateWindow(int width, int height, std::string name);
    void DeleteWindow();
    bool ShouldClose();
    void MakeCurrent();
    void Display();
    void Clear();
    void KeyPress(std::tuple<GLFWwindow*, int, int, int, int> key_call);
    void SetKeyAction(int key, int scan_code, int action, int mode,
                      void (*func)(GLFWwindow*));
    void CloseWindow();
    GLFWwindow* operator()();

   private:
    GLFWwindow* ptr = NULL;
    std::array<float, 4> clear_color{{0.0f, 0.0f, 0.0f, 1.0f}};
    std::map<std::array<int, 4>, void (*)(GLFWwindow*)> key_actions;
  };
}
#endif
