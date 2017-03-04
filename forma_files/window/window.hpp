#ifndef FORMA_WINDOW_WINDOW_HPP
#define FORMA_WINDOW_WINDOW_HPP
#include "../gl_headers.hpp"
#include <array>
#include <string>
namespace forma {
namespace window {
enum WindowPresets { RESIZEABLE = 0 };
class Window {
public:
  Window();
  ~Window();
  void WindowPreset(int preset, int setting);
  void CreateWindow(int width, int height, std::string name);
  bool ShouldClose();
  std::pair<int, int> GetSize();
  std::pair<int, int> GetFrameBufferSize();
  void Update();

private:
  GLFWwindow *gl_window;
  std::pair<int, int> window_size;
  std::array<int, 7> window_presets;
};
}
}
#endif
