#ifndef FORMA_SHADER_HPP
#define FORMA_SHADER_HPP
#include "../gl_headers.hpp"
#include <string>
#include <memory>
namespace forma{
  enum Shaders{
    FORMA_VERTEX_SHADER,
    FORMA_FRAGMENT_SHADER
  };
  class Shader{
    public:
      Shader();
      Shader(const Shader& copy);
      ~Shader();
      void AddShader(int shader, std::string shader_path);
      void CreateProgram();
      GLuint operator()(){return(*shader_program);}
    private:
      bool vs = false, gs = false, ts = false, fs = false;
      std::shared_ptr<GLuint> shader_program;
      GLuint vertex_shader, geometry_shader, tesselation_shader, fragment_shader;
  };
}
#endif
