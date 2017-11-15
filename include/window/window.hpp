#ifndef FORMA_WINDOW_WINDOW_HP
#define FORMA_WINDOW_WINDOW_HP

#include <functional>
#include <map>
#include <memory>

#include "../entity/entity.hpp"
#include "../gl.hpp"

namespace forma {
  namespace window {
    enum WindowActions { ACTION_NONE = 0, ACTION_QUIT = 1, ACTION_LOG = 2 };
    class Window {
     public:
      bool CreateWindow();
      bool DestroyWindow();

      void SetShouldClose(bool close);
      bool ShouldClose();

      void MakeCurrent();

      void SetViewPort();

      void Update();
      void Clear();
      void Display(entity::Entity* ptr);

      void SetKeyEvent(std::array<int, 4> key_info, unsigned int set_action);
      void SetKeyEvent(unsigned int key, unsigned int set_action);
      void SetKeyEvent(std::array<int, 4> key_info,
                       std::function<void(std::shared_ptr<GLFWwindow*>)> func);
      void SetKeyEvent(unsigned int key,
                       std::function<void(std::shared_ptr<GLFWwindow*>)> func);
      void ProcessEvents();

     private:
      bool GenerateWindow();
      bool TerminateWindow();

      void RunAction(unsigned int action);

      bool should_close_ = false;
      const char* name_ = "Aequus";
      std::array<unsigned int, 2> size_ = {{500, 500}};

      std::map<std::array<int, 4>, unsigned int> key_action_;
      std::map<std::array<int, 4>,
               std::function<void(std::shared_ptr<GLFWwindow*>)>>
          key_function_;

      std::shared_ptr<GLFWwindow*> window_ = NULL;
    };
  }  // namespace window
}  // namespace forma

#endif /* ifndef FORMA_WINDOW_WINDOW_HP */
