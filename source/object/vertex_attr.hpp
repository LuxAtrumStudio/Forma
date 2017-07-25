#ifndef FORMA_OBJECT_VERTEX_ATTR_HPP
#define FORMA_OBJECT_VERTEX_ATTR_HPP

#include <vector>

namespace forma {
  namespace object {
    struct VertexAttr {
     public:
      VertexAttr();
      VertexAttr(int pos, std::vector<float> data_);
      VertexAttr(int pos, int point, std::vector<float> data_);
      ~VertexAttr();

      int size = 0, position = 0;
      std::vector<float> data;

     private:
    };
  }  // namespace object
}  // namespace forma
#endif
