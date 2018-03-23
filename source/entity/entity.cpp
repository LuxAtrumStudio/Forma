#include "entity/entity.hpp"

#include <memory>
#include <numeric>
#include <vector>

#include <iostream>

#include "gl.hpp"
#include "log/logger.hpp"
#include "shader/shader.hpp"

forma::entity::Entity::Entity() {}

forma::entity::Entity::Entity(const Entity& copy) {
  entity_shader_ = copy.entity_shader_;
  vertices_ = copy.vertices_;
  indices_ = copy.indices_;
  vbo_ = copy.vbo_;
  vao_ = copy.vao_;
  ebo_ = copy.ebo_;
}

forma::entity::Entity::~Entity() {
  glDeleteVertexArrays(1, &vao_);
  glDeleteBuffers(1, &vbo_);
  glDeleteBuffers(1, &ebo_);
}

void forma::entity::Entity::SetDisplayMode(
    forma::entity::EntityDisplayMode mode) {
  display_mode_ = mode;
}

void forma::entity::Entity::SetShader(
    std::shared_ptr<forma::shader::Shader> shade) {
  entity_shader_ = shade;
}

void forma::entity::Entity::SetVerticies(std::vector<float> vertices) {
  vertices_ = vertices;
}

void forma::entity::Entity::SetVertexAttribute(std::string attr,
                                               std::vector<float> data,
                                               unsigned ptr, unsigned size) {
  std::size_t index = 0;
  bool match = false;
  for (auto& it : vertex_attributes_) {
    if (std::get<0>(it) == attr && ptr == 0) {
      std::get<2>(it) = size;
      std::get<3>(it) = data;
      match = true;
      break;
    } else if (std::get<1>(it) == ptr && ptr != 0) {
      logging::Warning("entity/entity.cpp",
                       "forma::entity::Entity::SetVertexAttribute(std::string, "
                       "std::vector<float>, unsigned, unsigned)",
                       "Vertex already has an attribute with the index %i "
                       "named %s. Overwriting with %s",
                       ptr, std::get<0>(it).c_str(), attr.c_str());
      std::get<0>(it) = attr;
      std::get<2>(it) = size;
      std::get<3>(it) = data;
      match = true;
      break;
    } else if (std::get<1>(it) > ptr && ptr != 0) {
      std::tuple<std::string, unsigned, unsigned, std::vector<float>> attribute(
          attr, ptr, size, data);
      vertex_attributes_.insert(vertex_attributes_.begin() + index, attribute);
      match = true;
      break;
    }
    index++;
  }
  if (match == false && ptr == 0) {
    std::tuple<std::string, unsigned, unsigned, std::vector<float>> attribute(
        attr, vertex_attributes_.size(), size, data);
    vertex_attributes_.push_back(attribute);
  } else if (match == false && ptr != 0) {
    std::tuple<std::string, unsigned, unsigned, std::vector<float>> attribute(
        attr, ptr, size, data);
    vertex_attributes_.push_back(attribute);
  }
}

void forma::entity::Entity::SetIndices(std::vector<unsigned> indices) {
  indices_ = indices;
}

void forma::entity::Entity::Display() {
  if (entity_shader_->IsValid() == true) {
    entity_shader_->Use();
  }
  glBindVertexArray(vao_);
  glDrawElements(display_mode_, indices_.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void forma::entity::Entity::CompileEntity() { GenerateObject(); }

void forma::entity::Entity::GenerateObject() {
  glGenVertexArrays(1, &vao_);
  if (vao_ == GL_INVALID_VALUE) {
    logging::Warning("entity/entity.cpp",
                     "forma::entity::Entity::GenerateObject()",
                     "Failed to generate vertex arrays");
  }
  if (indices_.size() == 0) {
    indices_ = std::vector<unsigned>(vertices_.size() / 3);
    std::iota(indices_.begin(), indices_.end(), 0);
  }
  std::vector<float> vbo_data;

  std::size_t vertex_index = 0;
  std::size_t vertex_length = 3;
  while (vertex_index < vertices_.size() / 3) {
    vbo_data.insert(vbo_data.end(), vertices_.begin() + (3 * vertex_index),
                    vertices_.begin() + (3 * vertex_index) + 3);
    for (auto& it : vertex_attributes_) {
      std::vector<float> ref = std::get<3>(it);
      unsigned size = std::get<2>(it);
      vbo_data.insert(vbo_data.end(), ref.begin() + (size * vertex_index),
                      ref.begin() + (size * vertex_index) + size);
      if(vertex_index == 0){
        vertex_length += size;
      }
    }
    vertex_index++;
  }
  glGenBuffers(1, &vbo_);
  glGenBuffers(1, &ebo_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vbo_data.size() * sizeof(float),
               vbo_data.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned),
               indices_.data(), GL_STATIC_DRAW);

  // Position Attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_length * sizeof(float),
                        (GLvoid*)0);
  glEnableVertexAttribArray(0);
  std::size_t offset = 3;
  for(auto &it : vertex_attributes_){
    glVertexAttribPointer(std::get<1>(it), std::get<2>(it), GL_FLOAT, GL_FALSE, vertex_length * sizeof(float),
                          (GLvoid*)(offset * sizeof(float)));
    glEnableVertexAttribArray(std::get<1>(it));
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
