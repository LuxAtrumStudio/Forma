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

      void SetBool(const std::string& name, bool value);
      void SetInt(const std::string& name, bool value);
      void SetFloat(const std::string& name, bool value);

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
