#ifndef FORMA_SHADER_SHADER_HPP
#define FORMA_SHADER_SHADER_HPP

#include <array>
#include <memory>
#include <string>

namespace forma {
  namespace shader {
    class Shader {
     public:
      Shader();
      Shader(const Shader& copy);
      ~Shader();

      void VertexShader(std::string shader);
      void FragmentShader(std::string shader);

      void CompileShader();
      void DestroyShader();

      bool IsValid();
      void Use();

      std::shared_ptr<forma::shader::Shader> GetPtr();

      void Uniform1f(const std::string& name, float v0);
      void Uniform2f(const std::string& name, float v0, float v1);
      void Uniform3f(const std::string& name, float v0, float v1, float v2);
      void Uniform4f(const std::string& name, float v0, float v1, float v2,
                     float v3);
      void Uniform1i(const std::string& name, int v0);
      void Uniform2i(const std::string& name, int v0, int v1);
      void Uniform3i(const std::string& name, int v0, int v1, int v2);
      void Uniform4i(const std::string& name, int v0, int v1, int v2, int v3);
      void Uniform1ui(const std::string& name, unsigned int v0);
      void Uniform2ui(const std::string& name, unsigned int v0,
                      unsigned int v1);
      void Uniform3ui(const std::string& name, unsigned int v0, unsigned int v1,
                      unsigned int v2);
      void Uniform4ui(const std::string& name, unsigned int v0, unsigned int v1,
                      unsigned int v2, unsigned int v3);

     private:
      inline bool FileExists(std::string name);
      unsigned int LoadShader(std::string name, unsigned int shader);

      std::array<std::string, 3> shaders_ = {
          {std::string(), std::string(), std::string()}};

      std::shared_ptr<unsigned int> id_ = NULL;
    };
  }  // namespace shader
}  // namespace forma

#endif /* ifndef FORMA_SHADER_SHADER_HPP */
