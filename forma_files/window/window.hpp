#ifndef FORMA_WINDOW_WINDOW_HPP
#define FORMA_WINDOW_WINDOW_HPP
#include "window_class.hpp"
#include <vector>
namespace forma {
namespace window {
extern std::vector<Window> forma_windows;
bool AllClosed();
void ShouldClose();
void UpdateAll();
int CreateWindow(int width, int height, std::string name);
}
}
#endif
