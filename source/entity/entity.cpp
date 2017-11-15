#include "entity/entity.hpp"

#include <memory>

#include "shader/shader.hpp"

forma::entity::Entity::Entity() {}

forma::entity::Entity::Entity(const Entity& copy) {}

forma::entity::Entity::~Entity() {}

void forma::entity::Entity::SetShader(
    std::shared_ptr<forma::shader::Shader> shade) {
  entity_shader_ = shade;
}

void forma::entity::Entity::Display() {
  if (entity_shader_->IsValid() == true) {
    entity_shader_->Use();
  }
}
