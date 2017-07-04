#ifndef FORMA_CORE_HPP
#define FORMA_CORE_HPP

#define FORMA_VERSION_MAJOR 0
#define FORMA_VERSION_MINOR 1
#define FORMA_VERSION_PATCH 2

#include <string>

namespace forma {
  void InitForma();
  void TermForma();

  void InitGlfw();
  void InitGlad();

  void TermGlfw();
  void TermGlad();

  void GetVersion(int& major, int& minor, int& patch);

  void GlfwError(int error_code, const char* error);

  void GladError();
}

#endif
