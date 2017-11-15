#ifndef FORMA_ENTITY_ENTITY_HPP
#define FORMA_ENTITY_ENTITY_HPP

#include <memory>
#include "../shader/shader.hpp"

namespace forma {
  namespace entity {
    class Entity {
     public:
      Entity();
      Entity(const Entity& copy);
      ~Entity();

      void SetShader(std::shared_ptr<forma::shader::Shader> shader);

      void Display();

     private:
      void GenerateObject();

      std::shared_ptr<forma::shader::Shader> entity_shader_;

      unsigned int vao_;
    };
  }  // namespace entity
}  // namespace forma

#endif /* ifndef FORMA_ENTITY_ENTITY_HPP */
