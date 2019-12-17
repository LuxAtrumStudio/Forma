#ifndef IMAGE_HPP_4I7NI2UF
#define IMAGE_HPP_4I7NI2UF

#include <glm/glm.hpp>

namespace forma {
  namespace image {
    enum PixelFormat { NONE, MONO, RGB, BGR, RGBA, BGRA };
    constexpr PixelFormatChannels(const PixelFormat& fmt) {
      switch (fmt) {
        case NONE:
          return 0;
        case MONO:
          return 1;
        case RGB:
          return 3;
        case BGR:
          return 3;
        case RGBA:
          return 4;
        case BGRA:
          return 5;
      }
    }
    struct Image {
      inline Image()
          : width(0), height(0), channels(0), format(NONE), pixels(nullptr) {}
      inline Image(const std::size_t& dim, PixelFormat fmt = RGB)
          : width(dim),
            height(dim),
            channels(PixelFormatChannels(fmt)),
            format(fmt) {
        pixels = (std::uint8_t*)std::malloc(sizeof(std::uint8_t) * channels *
                                            width * height);
      }
      inline Image(const std::size_t& width, const std::size_t& height,
                   PixelFormat fmt = RGB)
          : width(width),
            height(height),
            channels(PixelFormatChannels(fmt)),
            format(fmt) {
        pixels = (std::uint8_t*)std::malloc(sizeof(std::uint8_t) * channels *
                                            width * height);
      }
      inline ~Image() {
        if (pixels != nullptr) {
          free(pixels);
        }
      }
      std::size_t width, height, channels;
      PixelFormat format;
      std::uint8_t* pixels;
    };
  }  // namespace image
}  // namespace forma

#endif /* end of include guard: IMAGE_HPP_4I7NI2UF */
