#ifndef FORMA_GRAPHICS_WINDOW_BUILDER_HPP_
#define FORMA_GRAPHICS_WINDOW_BUILDER_HPP_

#include <cstdlib>
#include <string>

#include "../gl/gl.hpp"
#include "window.hpp"

namespace forma {
  namespace graphics {
    class WindowBuilder {
     public:
      inline WindowBuilder()
          : width_(100), height_(100), title_("FORMA"), fullscreen_(false) {}
      inline WindowBuilder& width(const std::uint32_t& v) {
        width_ = v;
        return *this;
      }
      inline WindowBuilder& height(const std::uint32_t& v) {
        height_ = v;
        return *this;
      }
      inline WindowBuilder& title(const std::string& v) {
        title_ = v;
        return *this;
      }
      inline WindowBuilder& fullscreen() {
        fullscreen_ = true;
        return *this;
      }
      inline WindowBuilder& windowed() {
        fullscreen_ = false;
        return *this;
      }
      inline Window build() {
        return Window(width_, height_, title_, fullscreen_);
      }

     private:
      std::uint32_t width_, height_;
      std::string title_;
      bool fullscreen_;
    };
  }  // namespace graphics
}  // namespace forma

#endif  // FORMA_GRAPHICS_WINDOW_BUILDER_HPP_
