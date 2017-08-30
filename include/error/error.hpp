#ifndef FORMA_ERROR_ERROR_HPP
#define FORMA_ERROR_ERROR_HPP

#include "../log/log.hpp"

namespace forma {
  namespace error {
    void GlfwErrorHandle(int error_num, const char* error_msg);
  }  // namespace error
}  // namespace forma
#endif /* ifndef FORMA_ERROR_ERROR_HPP */
