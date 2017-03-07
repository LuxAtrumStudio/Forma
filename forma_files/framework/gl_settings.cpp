#include <pessum.h>
#include <string>
#include "../gl_headers.hpp"
#include "gl_settings.hpp"

void forma::framework::PolygonMode(int face, int mode) {
  GLenum gl_face, gl_mode;
  if (face == 0) {
    gl_face = GL_FRONT;
  } else if (face == 1) {
    gl_face = GL_BACK;
  } else {
    gl_face = GL_FRONT_AND_BACK;
  }
  if (mode == 0) {
    gl_mode = GL_POINT;
  } else if (mode == 1) {
    gl_mode = GL_LINE;
  } else {
    gl_mode = GL_FILL;
  }
  glPolygonMode(gl_face, gl_mode);
}

void forma::framework::GlfwError(int error_code, const char* error) {
  pessum::logging::Log("error", error, "GLFW ERROR",
                       std::to_string(error_code));
}
