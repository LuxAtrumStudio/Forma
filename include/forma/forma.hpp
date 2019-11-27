#ifndef FORMA_HPP_
#define FORMA_HPP_

#include <cstdlib>
#include <string>
#include <functional>

#include "version.hpp"

/**
 * @brief Core graphics engine namespace
 */
namespace forma {
  bool initalize_logger(const bool& console_logger);
  bool create_window(const std::size_t& w, const std::size_t& h,
                     const std::string& title, bool fullscreen = false);
  bool close_window();

  void set_update(const std::function<void(const float&)> update);
  void run();
  void run(const std::function<void(const float&)> update);

  bool is_key_down(const Key& key);
}  // namespace forma

#endif  // FORMA_HPP_
