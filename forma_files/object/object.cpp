#include <vector>
#include "object.hpp"
#include "object_class.hpp"
#include "shader_class.hpp"

namespace forma {
  namespace object {
    std::vector<Shader> shaders;
    std::vector<Object> objects;
  }
}

int forma::object::CreateShader(std::string vertex_shader,
                                std::string fragment_shader) {
  Shader new_shader(vertex_shader, fragment_shader);
  new_shader.CreateShader();
  shaders.push_back(new_shader);
  return (shaders.size() - 1);
}

int forma::object::CreateObject() {
  objects.push_back(Object());
  return (objects.size() - 1);
}

void forma::object::DisplayAll() {
  for (int i = 0; i < objects.size(); i++) {
    objects[i].Display();
  }
}
