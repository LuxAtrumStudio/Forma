#ifndef FORMA_WINDOW_WINDOW_CLASS_HPP
#define FORMA_WINDOW_WINDOW_CLASS_HPP
#include <array>
#include <string>
#include "../gl_headers.hpp"
#include "../types/type_headers.hpp"
namespace forma {
namespace window {
  enum WindowPresets {
    RESIZEABLE = 0,
    VISIBLE = 1,
    DECORATED = 2,
    FOCUSED = 3,
    AUTO_ICONIFY = 4,
    FLOATING = 5,
    MAXIMIZED = 6
  };
  class Window {
   public:
    Window();
    Window(const Window& copy_window);
    ~Window();
    void WindowPreset(int preset, int setting);
    void CreateWindow(int width, int height, std::string name);
    void DeleteWindow();
    bool ShouldClose();
    std::pair<int, int> GetSize();
    std::pair<int, int> GetFrameBufferSize();
    void Update();
    void Clear();
    void SetClearColor(float red, float green, float blue, float alpha);

   private:
    void ReadPresets();
    quad<float, float, float, float> clear_color;
    GLFWwindow* gl_window = nullptr;
    std::pair<int, int> window_size;
    std::array<int, 7> window_presets;
  };
}
}
#endif
