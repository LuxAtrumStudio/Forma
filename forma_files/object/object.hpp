#ifndef FORMA_OBJECT_OBJECT_HPP
#define FORMA_OBJECT_OBJECT_HPP
#include <vector>
#include "object_class.hpp"
#include "shader_class.hpp"

namespace forma {
  namespace object {
    extern std::vector<Object> objects;
    int CreateObject();
    void DisplayAll();
  }
}
#endif
