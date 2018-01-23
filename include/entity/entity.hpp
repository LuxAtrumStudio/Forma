#ifndef FORMA_ENTITY_ENTITY_HPP
#define FORMA_ENTITY_ENTITY_HPP

#include <memory>
#include <vector>
#include "../shader/shader.hpp"

namespace forma {
  namespace entity {
    class Entity {
     public:
      Entity();
      Entity(const Entity& copy);
      ~Entity();

      void SetShader(std::shared_ptr<forma::shader::Shader> shader);
      void SetVerticies(std::vector<float> vertices);
      void SetIndices(std::vector<unsigned int> indices);

      void Display();

      void CompileEntity();

     private:
      void GenerateObject();

      std::shared_ptr<forma::shader::Shader> entity_shader_;
      std::vector<float> vertices_;
      std::vector<unsigned int> indices_;

      unsigned int vbo_, vao_, ebo_;
    };
  }  // namespace entity
}  // namespace forma

#endif /* ifndef FORMA_ENTITY_ENTITY_HPP */
