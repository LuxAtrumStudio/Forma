#ifndef FORMA_OBJECT_OBJECT_CLASS_HPP
#define FORMA_OBJECT_OBJECT_CLASS_HPP
#include <string>
#include <vector>
#include "../types/type_headers.hpp"
namespace forma {
  namespace object {
    class Object {
     public:
      Object();
      Object(const Object& copy_object);
      ~Object();
      void SetVertices(std::vector<triple<float, float, float>> vertices);
      void SetVertices(std::vector<float> vertices);
      void SetIndices(std::vector<int> indices);
      void Display();
      void SetShaderProgram(int index);
      void CreateObject();

     private:
      void CreateVao();
      unsigned int vao, vbo, ebo;
      int shader_program_index = 0;
      std::vector<triple<float, float, float>> obj_vertices;
      std::vector<int> obj_indices;
      // unsigned int gl_vbo, gl_shader_program, gl_vao, gl_ebo;
    };
  }
}
#endif
