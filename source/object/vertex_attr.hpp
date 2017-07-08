#ifndef FORMA_OBJECT_VERTEX_ATTR_HPP
#define FORMA_OBJECT_VERTEX_ATTR_HPP

#include <vector>

namespace forma {
  namespace object {
    struct VertexAttr {
     public:
      VertexAttr();
      VertexAttr(int pos, std::vector<float> data);
      VertexAttr(int pos, int point, std::vector<float> data);
      ~VertexAttr();

      int size = 0, position = 0;
      std::vector<float> vertices;

     private:
    };
  }
}
#endif
