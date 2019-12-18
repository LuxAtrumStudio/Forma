#ifndef IMAGE_HPP_4I7NI2UF
#define IMAGE_HPP_4I7NI2UF

#include <GLFW/glfw3.h>

#include <string_view>

#include "math.hpp"

namespace forma {
  namespace image {
    enum PixelFormat { NONE, MONO, GA, RGB, BGR, RGBA, BGRA };
    constexpr std::size_t pixel_format_channels(const PixelFormat& fmt) {
      switch (fmt) {
        case NONE:
          return 0;
        case MONO:
          return 1;
        case GA:
          return 2;
        case RGB:
          return 3;
        case BGR:
          return 3;
        case RGBA:
          return 4;
        case BGRA:
          return 5;
      }
      return 0;
    }
    struct Image {
      inline Image()
          : width(0), height(0), channels(0), format(NONE), pixels(nullptr) {}
      inline Image(const std::size_t& dim, PixelFormat fmt = RGB)
          : width(dim),
            height(dim),
            channels(pixel_format_channels(fmt)),
            format(fmt) {
        pixels = (std::uint8_t*)std::malloc(sizeof(std::uint8_t) * channels *
                                            width * height);
      }
      inline Image(const std::size_t& width, const std::size_t& height,
                   PixelFormat fmt = RGB)
          : width(width),
            height(height),
            channels(pixel_format_channels(fmt)),
            format(fmt) {
        pixels = (std::uint8_t*)std::malloc(sizeof(std::uint8_t) * channels *
                                            width * height);
      }
      inline Image(const std::size_t& width, const std::size_t& height,
                   std::uint8_t* data, PixelFormat fmt = RGB)
          : width(width),
            height(height),
            channels(pixel_format_channels(fmt)),
            format(fmt),
            pixels(data) {}
      inline ~Image() {
        if (pixels != nullptr) {
          free(pixels);
        }
      }

      operator GLFWimage() const {
        return GLFWimage{static_cast<int>(width), static_cast<int>(height),
                         pixels};
      }

      inline bool is_valid() const { return pixels != nullptr; }

      std::size_t width, height, channels;
      PixelFormat format;
      std::uint8_t* pixels;
    };

    Image load(const std::string_view& file_path);
    bool save(const std::string_view& file_path, const Image& img,
              bool flip = false);
  }  // namespace image
}  // namespace forma

#endif /* end of include guard: IMAGE_HPP_4I7NI2UF */
