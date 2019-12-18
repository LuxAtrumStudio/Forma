#ifndef COLOR_HPP_VYAV8UTF
#define COLOR_HPP_VYAV8UTF

#include <string>
#include <vector>

#include "math.hpp"

namespace forma {
  inline vec4 rgb(const float& r, const float& g, const float& b) {
    return {r, g, b, 1.0f};
  }
  inline vec4 rgb(const float& r, const float& g, const float& b,
                  const float& a) {
    return {r, g, b, a};
  }
  inline vec4 rgb(const std::uint8_t& r, const std::uint8_t& g,
                  const std::uint8_t& b) {
    return {static_cast<float>(r) / 255.0f, static_cast<float>(g) / 255.0f,
            static_cast<float>(b) / 255.0f, 1.0f};
  };
  inline vec4 rgb(const std::uint8_t& r, const std::uint8_t& g,
                  const std::uint8_t& b, const std::uint8_t& a) {
    return {static_cast<float>(r) / 255.0f, static_cast<float>(g) / 255.0f,
            static_cast<float>(b) / 255.0f, static_cast<float>(a) / 255.0f};
  };
  inline vec4 rgb(const std::uint32_t& color) {
    return {static_cast<float>((color >> 16) & 0xff) / 255.0f,
            static_cast<float>((color >> 8) & 0xff) / 255.0f,
            static_cast<float>((color >> 0) & 0xff) / 255.0f, 1.0f};
  }
  inline vec4 rgb(const std::string& str) {
    std::size_t pos = (str[0] == '#') ? 1 : 0;
    std::uint32_t color = std::stoul(str, &pos, 16);
    if (str.length() >= 8) {
      return {
          static_cast<float>((color >> 24) & 0xff) / 255.0f,
          static_cast<float>((color >> 16) & 0xff) / 255.0f,
          static_cast<float>((color >> 8) & 0xff) / 255.0f,
          static_cast<float>((color >> 0) & 0xff) / 255.0f,
      };
    } else {
      return {static_cast<float>((color >> 16) & 0xff) / 255.0f,
              static_cast<float>((color >> 8) & 0xff) / 255.0f,
              static_cast<float>((color >> 0) & 0xff) / 255.0f, 1.0f};
    }
  }

  vec3 spectral_to_xyz(const std::vector<float>& values,
                       const std::size_t& start, const std::size_t& end);
  vec3 spectral_to_lab(const std::vector<float>& values,
                       const std::size_t& start, const std::size_t& end);
  vec3 spectral_to_rgb(const std::vector<float>& values,
                       const std::size_t& start, const std::size_t& end);
  vec3 spectral_to_hsv(const std::vector<float>& values,
                       const std::size_t& start, const std::size_t& end);
  vec3 spectral_to_hsl(const std::vector<float>& values,
                       const std::size_t& start, const std::size_t& end);

  vec3 xyz_to_lab(const float& x, const float& y, const float& z);
  vec3 xyz_to_rgb(const float& x, const float& y, const float& z);
  vec3 xyz_to_hsv(const float& x, const float& y, const float& z);
  vec3 xyz_to_hsl(const float& x, const float& y, const float& z);
  vec3 lab_to_xyz(const float& l, const float& a, const float& b);
  vec3 lab_to_rgb(const float& l, const float& a, const float& b);
  vec3 lab_to_hsv(const float& l, const float& a, const float& b);
  vec3 lab_to_hsl(const float& l, const float& a, const float& b);
  vec3 rgb_to_xyz(const float& r, const float& g, const float& b);
  vec3 rgb_to_lab(const float& r, const float& g, const float& b);
  vec3 rgb_to_hsv(const float& r, const float& g, const float& b);
  vec3 rgb_to_hsl(const float& r, const float& g, const float& b);
  vec3 hsv_to_xyz(const float& h, const float& s, const float& v);
  vec3 hsv_to_lab(const float& h, const float& s, const float& v);
  vec3 hsv_to_rgb(const float& h, const float& s, const float& v);
  vec3 hsv_to_hsl(const float& h, const float& s, const float& v);
  vec3 hsl_to_xyz(const float& h, const float& s, const float& l);
  vec3 hsl_to_lab(const float& h, const float& s, const float& l);
  vec3 hsl_to_rgb(const float& h, const float& s, const float& l);
  vec3 hsl_to_hsv(const float& h, const float& s, const float& l);

  inline vec3 xyz_to_lab(const vec3& v) { return xyz_to_lab(v.x, v.y, v.z); }
  inline vec3 xyz_to_rgb(const vec3& v) { return xyz_to_rgb(v.x, v.y, v.z); }
  inline vec3 xyz_to_hsv(const vec3& v) { return xyz_to_hsv(v.x, v.y, v.z); }
  inline vec3 xyz_to_hsl(const vec3& v) { return xyz_to_hsl(v.x, v.y, v.z); }
  inline vec3 lab_to_xyz(const vec3& v) { return lab_to_xyz(v.x, v.y, v.z); }
  inline vec3 lab_to_rgb(const vec3& v) { return lab_to_rgb(v.x, v.y, v.z); }
  inline vec3 lab_to_hsv(const vec3& v) { return lab_to_hsv(v.x, v.y, v.z); }
  inline vec3 lab_to_hsl(const vec3& v) { return lab_to_hsl(v.x, v.y, v.z); }
  inline vec3 rgb_to_xyz(const vec3& v) { return rgb_to_xyz(v.x, v.y, v.z); }
  inline vec3 rgb_to_lab(const vec3& v) { return rgb_to_lab(v.x, v.y, v.z); }
  inline vec3 rgb_to_hsv(const vec3& v) { return rgb_to_hsv(v.x, v.y, v.z); }
  inline vec3 rgb_to_hsl(const vec3& v) { return rgb_to_hsl(v.x, v.y, v.z); }
  inline vec3 hsv_to_xyz(const vec3& v) { return hsv_to_xyz(v.x, v.y, v.z); }
  inline vec3 hsv_to_lab(const vec3& v) { return hsv_to_lab(v.x, v.y, v.z); }
  inline vec3 hsv_to_rgb(const vec3& v) { return hsv_to_rgb(v.x, v.y, v.z); }
  inline vec3 hsv_to_hsl(const vec3& v) { return hsv_to_hsl(v.x, v.y, v.z); }
  inline vec3 hsl_to_xyz(const vec3& v) { return hsl_to_xyz(v.x, v.y, v.z); }
  inline vec3 hsl_to_lab(const vec3& v) { return hsl_to_lab(v.x, v.y, v.z); }
  inline vec3 hsl_to_rgb(const vec3& v) { return hsl_to_rgb(v.x, v.y, v.z); }
  inline vec3 hsl_to_hsv(const vec3& v) { return hsl_to_hsv(v.x, v.y, v.z); }

  inline vec3 gradient(const vec3& a, const vec3& b, const float& t) {
    return glm::mix(a, b, t);
  }
  inline vec3 gradient_xyz_with_lab(const vec3& a, const vec3& b,
                                    const float& t) {
    return lab_to_xyz(glm::mix(xyz_to_lab(a), xyz_to_lab(b), t));
  }
  inline vec3 gradient_xyz_with_rgb(const vec3& a, const vec3& b,
                                    const float& t) {
    return rgb_to_xyz(glm::mix(xyz_to_rgb(a), xyz_to_rgb(b), t));
  }
  inline vec3 gradient_xyz_with_hsv(const vec3& a, const vec3& b,
                                    const float& t) {
    return hsv_to_xyz(glm::mix(xyz_to_hsv(a), xyz_to_hsv(b), t));
  }
  inline vec3 gradient_xyz_with_hsl(const vec3& a, const vec3& b,
                                    const float& t) {
    return hsl_to_xyz(glm::mix(xyz_to_hsl(a), xyz_to_hsl(b), t));
  }
  inline vec3 gradient_lab_with_xyz(const vec3& a, const vec3& b,
                                    const float& t) {
    return xyz_to_lab(glm::mix(lab_to_xyz(a), lab_to_xyz(b), t));
  }
  inline vec3 gradient_lab_with_rgb(const vec3& a, const vec3& b,
                                    const float& t) {
    return rgb_to_lab(glm::mix(lab_to_rgb(a), lab_to_rgb(b), t));
  }
  inline vec3 gradient_lab_with_hsv(const vec3& a, const vec3& b,
                                    const float& t) {
    return hsv_to_lab(glm::mix(lab_to_hsv(a), lab_to_hsv(b), t));
  }
  inline vec3 gradient_lab_with_hsl(const vec3& a, const vec3& b,
                                    const float& t) {
    return hsl_to_lab(glm::mix(lab_to_hsl(a), lab_to_hsl(b), t));
  }
  inline vec3 gradient_rgb_with_xyz(const vec3& a, const vec3& b,
                                    const float& t) {
    return xyz_to_rgb(glm::mix(rgb_to_xyz(a), rgb_to_xyz(b), t));
  }
  inline vec3 gradient_rgb_with_lab(const vec3& a, const vec3& b,
                                    const float& t) {
    return lab_to_rgb(glm::mix(rgb_to_lab(a), rgb_to_lab(b), t));
  }
  inline vec3 gradient_rgb_with_hsv(const vec3& a, const vec3& b,
                                    const float& t) {
    return hsv_to_rgb(glm::mix(rgb_to_hsv(a), rgb_to_hsv(b), t));
  }
  inline vec3 gradient_rgb_with_hsl(const vec3& a, const vec3& b,
                                    const float& t) {
    return hsl_to_rgb(glm::mix(rgb_to_hsl(a), rgb_to_hsl(b), t));
  }
  inline vec3 gradient_hsv_with_xyz(const vec3& a, const vec3& b,
                                    const float& t) {
    return xyz_to_hsv(glm::mix(hsv_to_xyz(a), hsv_to_xyz(b), t));
  }
  inline vec3 gradient_hsv_with_lab(const vec3& a, const vec3& b,
                                    const float& t) {
    return lab_to_hsv(glm::mix(hsv_to_lab(a), hsv_to_lab(b), t));
  }
  inline vec3 gradient_hsv_with_rgb(const vec3& a, const vec3& b,
                                    const float& t) {
    return rgb_to_hsv(glm::mix(hsv_to_rgb(a), hsv_to_rgb(b), t));
  }
  inline vec3 gradient_hsv_with_hsl(const vec3& a, const vec3& b,
                                    const float& t) {
    return hsl_to_hsv(glm::mix(hsv_to_hsl(a), hsv_to_hsl(b), t));
  }
  inline vec3 gradient_hsl_with_xyz(const vec3& a, const vec3& b,
                                    const float& t) {
    return xyz_to_hsl(glm::mix(hsl_to_xyz(a), hsl_to_xyz(b), t));
  }
  inline vec3 gradient_hsl_with_lab(const vec3& a, const vec3& b,
                                    const float& t) {
    return lab_to_hsl(glm::mix(hsl_to_lab(a), hsl_to_lab(b), t));
  }
  inline vec3 gradient_hsl_with_rgb(const vec3& a, const vec3& b,
                                    const float& t) {
    return rgb_to_hsl(glm::mix(hsl_to_rgb(a), hsl_to_rgb(b), t));
  }
  inline vec3 gradient_hsl_with_hsv(const vec3& a, const vec3& b,
                                    const float& t) {
    return hsv_to_hsl(glm::mix(hsl_to_hsv(a), hsl_to_hsv(b), t));
  }

}  // namespace forma

#endif /* end of include guard: COLOR_HPP_VYAV8UTF */
