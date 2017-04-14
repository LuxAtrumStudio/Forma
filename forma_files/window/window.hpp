#ifndef FORMA_WINDOW_HPP
#define FORMA_WINDOW_HPP
#include <array>
#include <string>
#include "../gl_headers.hpp"
namespace forma {
  class Window {
   public:
    void Preset(int option, int setting);
    void CreateWindow(int width, int height, std::string name);
    void DeleteWindow();
    bool ShouldClose();
    void Display();
    void Clear();

   private:
    GLFWwindow* ptr = NULL;
    std::array<float, 4> clear_color{{0.0f, 0.0f, 0.0f, 1.0f}};
  };
}
#endif
