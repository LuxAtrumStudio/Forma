#ifndef FORMA_OBJECT_SHADER_CLASS_HPP
#define FORMA_OBJECT_SHADER_CLASS_HPP
#include <string>
#include "../types/type_headers.hpp"
namespace forma {
  namespace object {
    enum ShaderType { VERTEX = 0, FRAGMENT = 1 };
    class Shader {
     public:
      Shader();
      Shader(std::string vertex_shader, std::string fragment_shader);
      Shader(const Shader& copy_shader);
      ~Shader();
      void CreateShader();
      void DeleteShader();
      void SetShaderFile(int shader, std::string file_path);
      unsigned int GetShaderProgram();
      void UseShader();

     private:
      unsigned int shader_program = 0;
      std::string ReadShaderFile(std::string file_path);
      std::pair<std::string, std::string> shader_file_path;
    };
  }
}
#endif
