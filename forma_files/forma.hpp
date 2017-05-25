#ifndef FORMA_FORMA_HPP
#define FORMA_FORMA_HPP

#define FORMA_VERSON_MAJOR 0
#define FORMA_VERSION_MINOR 0
#define FORMA_VERSION_PATCH 4

#include <string>
#include "gl_headers.hpp"
#include "window/window.hpp"

namespace forma {
  void InitForma();
  void TermForma();
  void InitGlfw(int v_major = GL_VERSION_MAJOR, int v_minor = GL_VERSION_MINOR);
  void InitGlew();
  void GlError(int error_code, const char* error);
  void GlError(GLenum err);
  void SetWindowPreset(int setting, bool value);
  void GetVersion(int& major, int& minor, int& patch);
}
#endif
