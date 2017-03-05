#include <vector>
#include "object_class.hpp"
#include "shader.hpp"
#include "shader_class.hpp"

namespace forma {
  namespace object {
    std::vector<Shader> shaders;
  }
}

int forma::object::CreateShader(std::string vertex_shader,
                                std::string fragment_shader) {
  Shader new_shader(vertex_shader, fragment_shader);
  new_shader.CreateShader();
  shaders.push_back(new_shader);
  return (shaders.size() - 1);
}
