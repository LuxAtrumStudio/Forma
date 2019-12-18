#ifndef GL_HPP_IKAC3VE9
#define GL_HPP_IKAC3VE9

#include "glad.h"

#include <GLFW/glfw3.h>

namespace forma {
  namespace gl {
    void set_error_callback();
    void log_glfw_warn();
    void log_glfw_error();
    void log_glfw_critical();
    bool init_glfw();
    bool term_glfw();
    bool load_gl();
  }  // namespace gl
}  // namespace forma

#endif /* end of include guard: GL_HPP_IKAC3VE9 */
