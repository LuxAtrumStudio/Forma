#ifndef FORMA_OBJECT_OBJECT_HPP
#define FORMA_OBJECT_OBJECT_HPP

#include <map>
#include <vector>

#include "../gl_headers.hpp"
#include "../shader/shader.hpp"
#include "vertex_attr.hpp"

namespace forma {
  namespace object {
    class Object {
     public:
      Object();
      Object(const Object& copy);
      ~Object();

      void CreateObject();

      void SetVertices(std::vector<float> vertices);
      void AddVertexAttr(std::string name, int ptr, int size,
                         std::vector<float> data);

     protected:
     private:
      void GenerateObject();
      std::map<std::string, VertexAttr> vertex_data;
      std::vector<int> indices;
    };
  }
}

#endif
