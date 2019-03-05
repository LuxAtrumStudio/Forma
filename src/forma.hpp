#ifndef FORMA_FORMA_HPP_
#define FORMA_FORMA_HPP_

namespace forma {
#define FORMA_VERSION_MAJOR 0
#define FORMA_VERSION_MINOR 0

  inline unsigned get_version_major() { return FORMA_VERSION_MAJOR; }
  inline unsigned get_version_minor() { return FORMA_VERSION_MINOR; }

  void set_log_verbosity(unsigned char verbosity);

}  // namespace forma

#endif  // FORMA_FORMA_HPP_
