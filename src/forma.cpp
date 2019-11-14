#include "forma/forma.hpp"

#include "forma/gl/gl.hpp"
#include "forma/graphics/graphics.hpp"
#include "forma/log.hpp"
#include "forma/version.hpp"

static bool is_initalized_ = false;

bool forma::initalize(bool console_logger) {
  if (!logger::initalize_logger(console_logger)) return false;
  LINFO("FORMA v{}.{}.{}", FORMA_VERSION_MAJOR, FORMA_VERSION_MINOR,
        FORMA_VERSION_PATCH);
  return graphics::initalize();
}

bool forma::terminate() {
  if (!is_initalized_) return true;
  return graphics::terminate();
}

bool forma::is_initalized() { return is_initalized_; }
