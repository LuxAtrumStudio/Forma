#ifndef FORMA_WINDOW_WINDOW_HPP
#define FORMA_WINDOW_WINDOW_HPP

#include <array>
#include <memory>
#include <tuple>
#include <vector>

#include "../gl_headers.hpp"

namespace forma {
  namespace window {
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

    enum WindoweActions { QUIT };

    class Window {
      enum FullscreenMode { DEFAULT = 1, BORDERLESS = 2 };

     public:
      Window();
      explicit Window(unsigned int state);
      Window(int width, int height, unsigned int state = 0);
      Window(const Window& copy);
      ~Window();

      void Delete();
      void Close();

      void MakeCurrent();
      void SetViewport();

      void Update();

      void SetKeyAction(std::array<int, 4> key_info,
                        void (*func)(std::shared_ptr<GLFWwindow*>));
      void SetKeyAction(std::array<int, 4> key_info, int action);
      void KeyCallback(std::array<int, 4> key_info);

      std::shared_ptr<GLFWwindow*> operator()();

     protected:
     private:
      void GenorateWindow();
      void ReadState(unsigned int state);
      std::shared_ptr<GLFWwindow*> ptr = NULL;
      std::vector<std::tuple<std::array<int, 4>, int,
                             void (*)(std::shared_ptr<GLFWwindow*>)>>
          key_actions;
      std::array<int, 2> size = {{958, 1051}};
      std::string name;
      int full_screen = 0;
    };
  }  // namespace window
}  // namespace forma

#endif
