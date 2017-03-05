#ifndef FORMA_FRAMEWORK_INITIALIZE_HPP
#define FORMA_FRAMEWORK_INITIALIZE_HPP
#include "../gl_macros.hpp"
namespace forma {
  namespace framework {
    void InitGlfw();
    void InitGlew();
    void GlfwVersion(int major = GL_VERSION_MAJOR,
                     int minor = GL_VERSION_MINOR);
    void GlfwProfile();
    void SetViewPort(int width = 0, int height = 0);
  }
}
#endif
