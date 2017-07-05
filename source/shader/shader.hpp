#ifndef FORMA_SHADER_SHADER_HPP
#define FORMA_SHADER_SHADER_HPP

#include <array>
#include <memory>
#include <string>

namespace forma {
  namespace shader {
    enum Shaders {
      VERTEX = 0,
      GEOMETRY = 1,
      FRAGMENT = 2,
    };
    class Shader {
     public:
      Shader();
      Shader(const Shader& copy);
      ~Shader();

      void CreateProgram();

      void AddShader(int shader, std::string& shader_path);

      void AddUniformi(std::string& name, int v0);
      void AddUniformi(std::string& name, int v0, int v1);
      void AddUniformi(std::string& name, int v0, int v1, int v2);
      void AddUniformi(std::string& name, int v0, int v1, int v2, int v3);
      void AddUniformui(std::string& name, unsigned int v0);
      void AddUniformui(std::string& name, unsigned int v0, unsigned int v1);
      void AddUniformui(std::string& name, unsigned int v0, unsigned int v1,
                        unsigned int v2);
      void AddUniformui(std::string& name, unsigned int v0, unsigned int v1,
                        unsigned int v2, unsigned int v3);
      void AddUniformf(std::string& name, float v0);
      void AddUniformf(std::string& name, float v0, float v1);
      void AddUniformf(std::string& name, float v0, float v1, float v2);
      void AddUniformf(std::string& name, float v0, float v1, float v2,
                       float v3);

      unsigned int operator()();

     protected:
     private:
      std::string GetShaderString(std::string shader_path);
      std::string GetDefaultShader(int shader);

      int GetUniformLocation(std::string name);

      std::shared_ptr<unsigned int> program = NULL;
      std::array<std::pair<bool, unsigned int>, 3> shaders = {
          {{false, 0}, {false, 0}, {false, 0}}};
    };
  }  // namesapce shader
}  // namespace forma
#endif
