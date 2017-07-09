#include "vertex_attr.hpp"

#include <vector>

forma::object::VertexAttr::VertexAttr() {}

forma::object::VertexAttr::~VertexAttr() { data.clear(); }

forma::object::VertexAttr::VertexAttr(int pos, std::vector<float> data_)
    : position(pos), data(data_) {
  bool full = false;
  int i = 2;
  while (full == false) {
    if (data.size() % i == 0) {
      full = true;
    }
  }
  size = i;
}

forma::object::VertexAttr::VertexAttr(int pos, int point,
                                      std::vector<float> data_)
    : size(point), position(pos), data(data_) {}
