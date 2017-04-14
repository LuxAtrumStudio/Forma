#ifndef FORMA_FORMA_HPP
#define FORMA_FORMA_HPP
#include <string>
#include "gl_headers.hpp"
#include "window/window.hpp"
namespace forma {
  Window InitForma(std::string name = "", int width = 500, int height = 500);
  void TermForma();
  void InitGlfw(int v_major = GL_VERSION_MAJOR, int v_minor = GL_VERSION_MINOR);
  void InitGlew();
  void GlError(int error_code, const char* error);
  void GlError(GLenum err);
  void SetWindowPreset(int setting, bool value);
}
#endif
