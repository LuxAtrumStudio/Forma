#ifndef FORMA_VIDEO_WINDOW_HPP_
#define FORMA_VIDEO_WINDOW_HPP_

#include <string>
#include <memory>

#include "../gl.hpp"

namespace forma {
  namespace video {
    class Window {
      public:
        Window();
        explicit Window(std::string name);
        Window(std::string name, uint16_t width, uint16_t height);
        ~Window();

        bool Create();
        bool Destroy();

        void SetShouldClose(bool close);
        bool ShouldClose() const;

        void MakeCurrent() const;

        void HandleEvents();

        std::string GetName() const;
        uint16_t GetWidth() const;
        uint16_t GetHeight() const;
      private:
        std::string name_;
        uint16_t width_, height_;

        bool should_close_;

        std::unique_ptr<GLFWwindow*> ptr_;
    };
  } // namespace video 
} // namespace forma
#endif  // FORMA_VIDEO_WINDOW_HPP_

