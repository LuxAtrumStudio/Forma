#include "forma.hpp"

bool forma::init() {
#ifndef DEV
  forma::log::Default()->set_activation(forma::log::FATAL | forma::log::ERROR |
                                        forma::log::INFO);
#endif
  forma::log::version("libforma v.%d.%d", FORMA_VERSION_MAJOR,
                      FORMA_VERSION_MINOR);
  return true;
}
