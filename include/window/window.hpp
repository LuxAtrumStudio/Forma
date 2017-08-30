#ifndef FORMA_WINDOW_WINDOW_HP
#define FORMA_WINDOW_WINDOW_HP

#include <memory>

#include "../gl.hpp"

namespace forma {
  namespace window {
    class Window {
     public:
      bool CreateWindow();
      bool DestroyWindow();

      void SetShouldClose(bool close);
      bool ShouldClose();

      void MakeCurrent();

      void SetViewPort();

      void Display();
      void Clear();

     private:
      bool GenerateWindow();
      bool TerminateWindow();

      bool should_close_ = false;
      const char* name_ = "Aequus";
      std::array<unsigned int, 2> size_ = {{500, 500}};

      std::shared_ptr<GLFWwindow*> window_ = NULL;
    };
  }  // namespace window
}  // namespace forma

#endif /* ifndef FORMA_WINDOW_WINDOW_HP */
