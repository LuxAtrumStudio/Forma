#ifndef FORMA_FORMA_HPP_
#define FORMA_FORMA_HPP_

#include "logger.hpp"

#define FORMA_VERSION_MAJOR 0
#define FORMA_VERSION_MINOR 0

namespace forma {

  bool init();

  inline unsigned get_version_major() { return FORMA_VERSION_MAJOR; }
  inline unsigned get_version_minor() { return FORMA_VERSION_MINOR; }

}  // namespace forma

#endif  // FORMA_FORMA_HPP_
