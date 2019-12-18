#include "forma/shader.hpp"

#include "forma/gl.hpp"

forma::shader::Shader(){}
forma::shader::Shader(const std::string& vs, const std::string& fs){}
forma::shader::~Shader(){}

void forma::shader::compile_shader(){}
void forma::shader::destroy_shader(){}

bool forma::shader::is_valid(){}
void forma::shader::use(){}

// template <typename T>
// void set(const std::string& name, T& a);
// template <typename T>
// void set(const std::string& name, T& a, T& b);
// template <typename T>
// void set(const std::string& name, T& a, T& b, T& c);
// template <typename T>
// void set(const std::string& name, T& a, T& b, T& c, T& d);
