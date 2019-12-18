#ifndef SHADER_HPP_H9WOKRQM
#define SHADER_HPP_H9WOKRQM

namespace forma {
  namespace shader {
    class Shader {
      Shader();
      Shader(const std::string& vs, const std::string& fs);
      ~Shader();

      void compile_shader();
      void destroy_shader();

      bool is_valid();
      void use();

      template <typename T>
      void set(const std::string& name, T& a);
      template <typename T>
      void set(const std::string& name, T& a, T& b);
      template <typename T>
      void set(const std::string& name, T& a, T& b, T& c);
      template <typename T>
      void set(const std::string& name, T& a, T& b, T& c, T& d);
    };
  }  // namespace shader
}  // namespace forma

#endif /* end of include guard: SHADER_HPP_H9WOKRQM */
