#ifndef SHADER_HPP_H9WOKRQM
#define SHADER_HPP_H9WOKRQM

#include <memory>

namespace forma {
  namespace shader {
    enum ShaderType { VERTEX, GEOMETRY, FRAGMENT };
    class Shader {
     public:
      Shader();
      Shader(const std::string& vs, const std::string& fs);
      Shader(const Shader& copy);
      ~Shader();

      bool compile_shader();
      void destroy_shader();

      bool is_valid() const;
      unsigned int get_program();
      void use();

      template <typename T>
      void set(const std::string& name, T& a);
      template <typename T>
      void set(const std::string& name, T& a, T& b);
      template <typename T>
      void set(const std::string& name, T& a, T& b, T& c);
      template <typename T>
      void set(const std::string& name, T& a, T& b, T& c, T& d);

     private:
      std::string vs_source, fs_source;
      std::shared_ptr<unsigned int> program_ptr;
    };
  }  // namespace shader
}  // namespace forma

#endif /* end of include guard: SHADER_HPP_H9WOKRQM */
