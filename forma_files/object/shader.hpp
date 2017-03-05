#ifndef FORMA_OBJECT_SHADER_HPP
#define FORMA_OBJECT_SHADER_HPP
#include <vector>
#include "object_class.hpp"
#include "shader_class.hpp"

namespace forma {
  namespace object {
    extern std::vector<Shader> shaders;
    int CreateShader(std::string vertex_shader = "",
                     std::string fragment_shader = "");
  }
}
#endif
