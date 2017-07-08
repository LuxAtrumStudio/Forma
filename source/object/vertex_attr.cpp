#include "vertex_attr.hpp"

#include <vector>

forma::object::VertexAttr::VertexAttr() {}

forma::object::VertexAttr::~VertexAttr() { vertices.clear(); }

forma::object::VertexAttr::VertexAttr(int pos, std::vector<float> data)
    : position(pos), vertices(data) {
  bool full = false;
  int i = 2;
  while (full == false) {
    if (vertices.size() % i == 0) {
      full = true;
    }
  }
  size = i;
}

forma::object::VertexAttr::VertexAttr(int pos, int point,
                                      std::vector<float> data)
    : size(point), position(pos), vertices(data) {}
