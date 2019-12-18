#include "forma/image.hpp"

#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "forma/log.hpp"
#include "stb_image_write.h"

forma::image::Image forma::image::load(const std::string& file_path) {
  int x, y, n;
  LINFO("Loading image from \"{}\"", file_path);
  std::uint8_t* pixel_data = stbi_load(file_path.c_str(), &x, &y, &n, 0);
  if (pixel_data == NULL) LWARN("Failed to load \"{}\" image", file_path);
  switch (n) {
    case 1:
      return Image(x, y, pixel_data, MONO);
    case 2:
      return Image(x, y, pixel_data, GA);
    case 3:
      return Image(x, y, pixel_data, RGB);
    case 4:
      return Image(x, y, pixel_data, RGBA);
    default:
      LWARN(
          "Failed to recognize the number of channels in image {}, expected 1 "
          "2 3 4",
          n);
      return Image();
  }
}
bool forma::image::save(const std::string& file_path, const Image& img,
                        bool flip) {
  LINFO("Writing image to \"{}\"", file_path);
  stbi_flip_vertically_on_write(flip);
  if (file_path.length() >= 4 &&
      file_path.compare(file_path.length() - 4, 4, ".png") == 0) {
    return stbi_write_png(file_path.c_str(), img.width, img.height,
                          img.channels, img.pixels,
                          sizeof(std::uint8_t) * img.width * img.channels) != 0;
  } else if (file_path.length() >= 4 &&
             file_path.compare(file_path.length() - 4, 4, ".bmp") == 0) {
    return stbi_write_bmp(file_path.c_str(), img.width, img.height,
                          img.channels, img.pixels) != 0;
  } else if (file_path.length() >= 4 &&
             file_path.compare(file_path.length() - 4, 4, ".tga") == 0) {
    return stbi_write_tga(file_path.c_str(), img.width, img.height,
                          img.channels, img.pixels) != 0;
  } else if (file_path.length() >= 4 &&
             file_path.compare(file_path.length() - 4, 4, ".jpg") == 0) {
    return stbi_write_jpg(file_path.c_str(), img.width, img.height,
                          img.channels, img.pixels, 75) != 0;
  } else if (file_path.length() >= 4 &&
             file_path.compare(file_path.length() - 4, 4, ".hdr") == 0) {
    float* hdr_pixel = (float*)std::malloc(sizeof(float) * img.width *
                                           img.height * img.channels);
    if (hdr_pixel == nullptr) {
      LWARN("Failed to allocate memory for HDR buffer");
      return false;
    }
    for (std::size_t i = 0; i < img.width * img.height * img.channels; ++i) {
      hdr_pixel[i] = static_cast<float>(img.pixels[i]) / 255.0f;
    }
    bool ret = stbi_write_hdr(file_path.c_str(), img.width, img.height,
                              img.channels, hdr_pixel) != 0;
    free(hdr_pixel);
    return ret;
  } else {
    LWARN(
        "Failed to write image to \"{}\" unrecognized file type, expected .png "
        ".bmp .tga .jpg .hdr",
        file_path);
    return false;
  }
}
