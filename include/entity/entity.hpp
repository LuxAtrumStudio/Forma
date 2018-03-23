#ifndef FORMA_ENTITY_ENTITY_HPP
#define FORMA_ENTITY_ENTITY_HPP

#include <map>
#include <memory>
#include <vector>
#include "../gl.hpp"
#include "../shader/shader.hpp"

namespace forma {
  namespace entity {
    enum EntityDisplayMode {
      POINTS = GL_POINT,
      LINE_STRIP = GL_LINE_STRIP,
      LINE_LOOP = GL_LINE_LOOP,
      LINES = GL_LINES,
      TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
      TRIANGLE_FAN = GL_TRIANGLE_FAN,
      TRIANGLES = GL_TRIANGLES
      // QUAD_STRIP = GL_QUAD_STRIP,
      // QUADS = GL_QUADS,
      // POLYGON = GL_POLYGON
    };
    class Entity {
     public:
      Entity();
      Entity(const Entity& copy);
      ~Entity();

      void SetDisplayMode(EntityDisplayMode mode);
      void SetShader(std::shared_ptr<forma::shader::Shader> shader);
      void SetVerticies(std::vector<float> vertices);
      void SetVertexAttribute(std::string attr, std::vector<float> data,
                              unsigned ptr=0, unsigned size=3);
      void RemoveVertexAttribute(std::string attr);
      void SetIndices(std::vector<unsigned> indices);

      void Display();

      void CompileEntity();

     private:
      struct VertexAttribute {
        unsigned int ptr, size;
        std::vector<float> data;
      };

      void GenerateObject();

      EntityDisplayMode display_mode_ = TRIANGLES;

      std::shared_ptr<forma::shader::Shader> entity_shader_;
      std::vector<float> vertices_;
      std::vector<
          std::tuple<std::string, unsigned, unsigned, std::vector<float>>>
          vertex_attributes_;
      std::vector<unsigned> indices_;

      unsigned int vbo_, vao_, ebo_;
    };
  }  // namespace entity
}  // namespace forma

#endif /* ifndef FORMA_ENTITY_ENTITY_HPP */
