#ifndef FORMA_FORMA_HPP
#define FORMA_FORMA_HPP

#define FORMA_VERSION_MAJOR 0
#define FORMA_VERSION_MINOR 1
#define FORMA_VERSION_PATCH 0

#include <string>

namespace forma{
  void InitForma();
  void TermForma();
  void GetVersion(int& major, int& minor, int& patch);
}

#endif
