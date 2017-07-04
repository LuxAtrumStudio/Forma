#ifndef FORMA_WINDOW_WINDOW_HPP
#define FORMA_WINDOW_WINDOW_HPP

#include <array>
#include <memory>

#include "../gl_headers.hpp"

namespace forma {
  enum WindowHints {
    RESIZABLE = (1u << 0),
    VISIBLE = (1u << 1),
    DECORATED = (1u << 2),
    FOCUSED = (1u << 3),
    AUTO_ICONIFY = (1u << 4),
    FLOATING = (1u << 5),
    MAXIMIZED = (1u << 6),
    FULLSCREEN = (1u << 7),
    BORDERLESS_FULLSCREEN = (1u << 8)
  };
  class Window {
    enum FullscreenMode { DEFAULT, BORDERLESS };

   public:
    Window();
    explicit Window(unsigned int state);
    Window(int width, int height, unsigned int state = 0);
    Window(const Window& copy);
    ~Window();

    void Delete();

    void MakeCurrent();
    void SetViewport();

    void Update();

    std::shared_ptr<GLFWwindow*> operator()();

   protected:
   private:
    void GenorateWindow();
    void ReadState(unsigned int state);
    std::shared_ptr<GLFWwindow*> ptr = NULL;
    std::array<int, 2> size = {{500, 500}};
    std::string name;
    int full_screen = 0;
  };
}  // namespace forma

#endif
