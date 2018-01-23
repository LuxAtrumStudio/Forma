#include "entity/entity.hpp"

#include <memory>
#include <vector>

#include "shader/shader.hpp"
#include "log/log.hpp"
#include "gl.hpp"

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

void forma::entity::Entity::SetShader(
    std::shared_ptr<forma::shader::Shader> shade) {
  entity_shader_ = shade;
}

void forma::entity::Entity::SetVerticies(std::vector<float> vertices) {
  vertices_ = vertices;
}

void forma::entity::Entity::SetIndices(std::vector<unsigned int> indices){
  indices_ = indices;
}

void forma::entity::Entity::Display() {
  if (entity_shader_->IsValid() == true) {
    entity_shader_->Use();
  }
  glBindVertexArray(vao_);
  glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void forma::entity::Entity::CompileEntity(){
  GenerateObject();
}

void forma::entity::Entity::GenerateObject(){
  glGenVertexArrays(1, &vao_);
  if (vao_ == GL_INVALID_VALUE){
    log::Log(log::WARNING, "Failed to generate vertex arrays",
             "forma::entity::Entity::GenerateObject");
  }
  glGenBuffers(1, &vbo_);
  glGenBuffers(1, &ebo_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(GLfloat), vertices_.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLint), indices_.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
