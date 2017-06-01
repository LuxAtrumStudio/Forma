#ifndef FORMA_SHADER_SHADER_HPP
#define FORMA_SHADER_SHADER_HPP
#include "../gl_headers.hpp"
#include <string>
#include <memory>
namespace forma{
  enum Shaders{
    FORMA_VERTEX_SHADER,
    FORMA_FRAGMENT_SHADER
  };
  enum UniformTypes{
    FORMA_INT,
    FORMA_UNSIGNED_INT,
    FORMA_FLOAT
  };
  class Shader{
    public:
      Shader();
      Shader(const Shader& copy);
      ~Shader();
      void AddShader(int shader, std::string shader_path);
      void Uniform(std::string name, int type, int number, ...);
      void CreateProgram();
      GLuint operator()();
      bool created = false;
    private:
      bool vs = false, gs = false, ts = false, fs = false;
      std::shared_ptr<GLuint> shader_program;
      GLuint vertex_shader, geometry_shader, tesselation_shader, fragment_shader;
  };
}
#endif
