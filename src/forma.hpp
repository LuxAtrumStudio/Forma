#ifndef FORMA_FORMA_HPP_
#define FORMA_FORMA_HPP_

#include "logger.hpp"
#include "window.hpp"

#define FORMA_VERSION_MAJOR 0
#define FORMA_VERSION_MINOR 0

namespace forma {

  bool init();
  bool terminate();

  inline unsigned get_version_major() { return FORMA_VERSION_MAJOR; }
  inline unsigned get_version_minor() { return FORMA_VERSION_MINOR; }

  void glfw_error_callback(int error, const char* msg);

}  // namespace forma

#endif  // FORMA_FORMA_HPP_
