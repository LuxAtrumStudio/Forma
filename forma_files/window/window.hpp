#ifndef FORMA_WINDOW_HPP
#define FORMA_WINDOW_HPP
#include <array>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include "../gl_headers.hpp"
namespace forma {
  class Window {
   public:
    Window();
    Window(int width, int height);
    Window(std::string name, int width, int height);
    Window(const Window& copy);
    ~Window();
    void Preset(int option, int setting);
    void CreateWindow(std::string name, int width, int height);
    void DeleteWindow();
    bool ShouldClose();
    void MakeCurrent();
    void Display();
    void Clear();
    void KeyPress(std::tuple<GLFWwindow*, int, int, int, int> key_call);
    void SetKeyAction(int key, int scan_code, int action, int mode,
                      void (*func)(std::shared_ptr<GLFWwindow*>));
    void CloseWindow();
    std::shared_ptr<GLFWwindow*> operator()();

   private:
    //  std::vector<std::
    std::shared_ptr<GLFWwindow*> ptr = NULL;
    std::array<float, 4> clear_color{{0.0f, 0.0f, 0.0f, 1.0f}};
    std::map<std::array<int, 4>, void (*)(std::shared_ptr<GLFWwindow*>)>
        key_actions;
  };
}
#endif
