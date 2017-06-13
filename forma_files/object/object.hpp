#ifndef FORMA_OBJECT_OBJECT_HPP
#define FORMA_OBJECT_OBJECT_HPP
#include "../gl_headers.hpp"
#include "../shader/shader_headers.hpp"
#include <string>
#include <vector>
#include <map>
namespace forma{
class Object{
  public:
    struct VertexAttrib{
      int ptr, size;
      std::vector<GLfloat> values;
    };
    Object();
    Object(const Object& copy);
    ~Object();

    void CreateObject();
    
    void SetVertices(std::vector<float> in_vertices);
    void AddVertexAttrib(std::string name, int ptr, int size, std::vector<float> in_values);
    void RemoveVertexAttrib(std::string name);
    void SetIndices(std::vector<int> in_indices);

    void SetShaderProgram(Shader in_shader_program);
    
    void Display();

  private:
    GLuint vao;
    Shader shader_program;
    std::map<std::string, VertexAttrib> vertex_data;
    std::vector<GLint> indices;
};
}
#endif
