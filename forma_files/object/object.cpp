#include <vector>
#include "object.hpp"
#include "object_class.hpp"
#include "shader_class.hpp"

namespace forma {
  namespace object {
    std::vector<Object> objects;
  }
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
