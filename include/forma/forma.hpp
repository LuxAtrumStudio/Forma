#ifndef FORMA_HPP_
#define FORMA_HPP_

#include <cstdlib>

#include "version.hpp"
#include "graphics/graphics.hpp"

/**
 * @brief Core graphics engine namespace
 */
namespace forma {
#ifdef DEBUG
  bool initalize(bool console_logger = true);
#else
  bool initalize(bool console_logger = false);
#endif
  bool terminate();

  bool is_initalized();
}  // namespace forma

#endif  // FORMA_HPP_
