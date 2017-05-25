#ifndef FORMA_OBJECT_HPP
#define FORMA_OBJECT_HPP
#include "../gl_headers.hpp"
#include "../shader/shader_headers.hpp"
#include <string>
#include <vector>
namespace forma{
class Object{
  public:
    Object();
    Object(const Object& copy);
    ~Object();

    void CreateObject();
    
    void SetVertices(std::vector<float> in_vertices);
    void SetIndices(std::vector<int> in_indices);

    void SetShaderProgram(Shader in_shader_program);
    
    void Display();

  private:
    GLuint vao;
    Shader shader_program;
    std::vector<float> vertices;
    std::vector<int> indices;
};
}
#endif
