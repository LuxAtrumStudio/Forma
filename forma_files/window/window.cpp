#include "window.hpp"
#include "window_class.hpp"
#include <vector>

namespace forma {
namespace window {
std::vector<Window> forma_windows;
}
}

bool forma::window::AllClosed() {
  if (forma_windows.size() == 0) {
    return (true);
  } else {
    return (false);
  }
}

void forma::window::ShouldClose() {
  for (int i = 0; i < forma_windows.size(); i++) {
    if (forma_windows[i].ShouldClose() == true) {
      forma_windows[i].DeleteWindow();
      forma_windows[i].~Window();
      forma_windows.erase(forma_windows.begin() + i);
    }
  }
}

void forma::window::UpdateAll() {
  ShouldClose();
  for (int i = 0; i < forma_windows.size(); i++) {
    forma_windows[i].Update();
  }
}

int forma::window::CreateWindow(int width, int height, std::string name) {
  Window new_window;
  new_window.CreateWindow(width, height, name);
  forma_windows.push_back(new_window);
  return (forma_windows.size() - 1);
}
