#include "forma/shader.hpp"

#include <cstdio>
#include <memory>
#include <string>

#include "forma/gl.hpp"
#include "forma/log.hpp"
#include "forma/math.hpp"

std::string load_shader_src(const std::string& file,
                            const forma::shader::ShaderType& type) {
  if (file == "") {
    if (type == forma::shader::ShaderType::VERTEX) {
      return "#version 330 core\n"
             "layout(location = 0) in vec3 aPos;\n"
             "void main() {\n"
             "  gl_Position = vec4(aPos, 1.0f);\n"
             "}";
    } else if (type == forma::shader::ShaderType::GEOMETRY) {
      return "#version 330 core\n"
             "layout(points) in;\n"
             "layout(line_strip, max_vertices = 2) out;\n"
             "void main() {\n"
             "  gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, "
             "0.0);\n"
             "  EmitVertex();\n"
             "  gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.0, 0.0, "
             "0.0);\n"
             "  EmitVertex();\n"
             "  EndPrimitive();\n"
             "}";
    } else if (type == forma::shader::ShaderType::FRAGMENT) {
      return "#version 330 core\n"
             "out vec4 color;\n"
             "void main() {"
             "  color = vec4(1.0f);"
             "}";
    }
  } else {
    FILE* load = fopen(file.c_str(), "r");
    if (load == nullptr) return file;
    char line[255];
    std::string src;
    while (fgets(line, sizeof(line), load) != nullptr) {
      src += line + '\n';
    }
    fclose(load);
    return src;
  }
  return "";
}

forma::shader::Shader::Shader()
    : vs_source(load_shader_src("", VERTEX)),
      fs_source(load_shader_src("", FRAGMENT)),
      program_ptr(nullptr) {}
forma::shader::Shader::Shader(const std::string& vs, const std::string& fs)
    : vs_source(load_shader_src(vs, VERTEX)),
      fs_source(load_shader_src(fs, FRAGMENT)),
      program_ptr(nullptr) {}
forma::shader::Shader::Shader(const Shader& copy)
    : vs_source(copy.vs_source),
      fs_source(copy.fs_source),
      program_ptr(copy.program_ptr) {}
forma::shader::Shader::~Shader() {
  if (program_ptr.use_count() == 1) {
    glDeleteProgram(*program_ptr);
    program_ptr = nullptr;
  }
}

bool forma::shader::Shader::compile_shader() {
  int success;
  program_ptr = std::make_shared<unsigned int>(glCreateProgram());

  unsigned int vs_shader = glCreateShader(GL_VERTEX_SHADER);
  const char* vs_shader_src = vs_source.c_str();
  glShaderSource(vs_shader, 1, &vs_shader_src, NULL);
  glCompileShader(vs_shader);
  glGetShaderiv(vs_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetShaderInfoLog(vs_shader, 512, NULL, info_log);
    LERROR("Failed to compile vertex shader \"{}\"", info_log);
    return false;
  }
  glAttachShader(*program_ptr, vs_shader);

  unsigned int fs_shader = glCreateShader(GL_FRAGMENT_SHADER);
  const char* fs_shader_src = fs_source.c_str();
  glShaderSource(fs_shader, 1, &fs_shader_src, NULL);
  glCompileShader(fs_shader);
  glGetShaderiv(fs_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetShaderInfoLog(fs_shader, 512, NULL, info_log);
    LERROR("Failed to compile fragment shader \"{}\"", info_log);
    return false;
  }
  glAttachShader(*program_ptr, fs_shader);

  glLinkProgram(*program_ptr);
  glGetProgramiv(*program_ptr, GL_LINK_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetProgramInfoLog(*program_ptr, 512, NULL, info_log);
    LERROR("Failed to link shader program \"{}\"", info_log);
    return false;
  }

  glDeleteShader(vs_shader);
  glDeleteShader(fs_shader);
  vs_source = "";
  fs_source = "";
  return true;
}
void forma::shader::Shader::destroy_shader() {
  glDeleteProgram(*program_ptr);
  program_ptr = nullptr;
}

bool forma::shader::Shader::is_valid() const {
  if (program_ptr != nullptr) return true;
  return false;
}
unsigned int forma::shader::Shader::get_program() {
  if (program_ptr != nullptr) return *program_ptr;
  return 0;
}
void forma::shader::Shader::use() {
  if (program_ptr != nullptr) glUseProgram(*program_ptr);
}

template <>
void forma::shader::Shader::set(const std::string& name, int& a) {
  glUniform1i(glGetUniformLocation(*program_ptr, name.c_str()), a);
}
template <>
void forma::shader::Shader::set(const std::string& name, unsigned int& a) {
  glUniform1ui(glGetUniformLocation(*program_ptr, name.c_str()), a);
}
template <>
void forma::shader::Shader::set(const std::string& name, float& a) {
  glUniform1f(glGetUniformLocation(*program_ptr, name.c_str()), a);
}
template <>
void forma::shader::Shader::set(const std::string& name, const uvec2& v) {
  glUniform2ui(glGetUniformLocation(*program_ptr, name.c_str()), v.x, v.y);
}
template <>
void forma::shader::Shader::set(const std::string& name, const vec2& v) {
  glUniform2f(glGetUniformLocation(*program_ptr, name.c_str()), v.x, v.y);
}
template <>
void forma::shader::Shader::set(const std::string& name, const uvec3& v) {
  glUniform3ui(glGetUniformLocation(*program_ptr, name.c_str()), v.x, v.y, v.z);
}
template <>
void forma::shader::Shader::set(const std::string& name, const vec3& v) {
  glUniform3f(glGetUniformLocation(*program_ptr, name.c_str()), v.x, v.y, v.z);
}
template <>
void forma::shader::Shader::set(const std::string& name, const uvec4& v) {
  glUniform4ui(glGetUniformLocation(*program_ptr, name.c_str()), v.x, v.y, v.z,
               v.w);
}
template <>
void forma::shader::Shader::set(const std::string& name, const vec4& v) {
  glUniform4f(glGetUniformLocation(*program_ptr, name.c_str()), v.x, v.y, v.z,
              v.w);
}
template <>
void forma::shader::Shader::set(const std::string& name, int& a, int& b) {
  glUniform2i(glGetUniformLocation(*program_ptr, name.c_str()), a, b);
}
template <>
void forma::shader::Shader::set(const std::string& name, unsigned int& a,
                                unsigned int& b) {
  glUniform2ui(glGetUniformLocation(*program_ptr, name.c_str()), a, b);
}
template <>
void forma::shader::Shader::set(const std::string& name, float& a, float& b) {
  glUniform2f(glGetUniformLocation(*program_ptr, name.c_str()), a, b);
}
template <>
void forma::shader::Shader::set(const std::string& name, int& a, int& b,
                                int& c) {
  glUniform3i(glGetUniformLocation(*program_ptr, name.c_str()), a, b, c);
}
template <>
void forma::shader::Shader::set(const std::string& name, unsigned int& a,
                                unsigned int& b, unsigned int& c) {
  glUniform3ui(glGetUniformLocation(*program_ptr, name.c_str()), a, b, c);
}
template <>
void forma::shader::Shader::set(const std::string& name, float& a, float& b,
                                float& c) {
  glUniform3f(glGetUniformLocation(*program_ptr, name.c_str()), a, b, c);
}
template <>
void forma::shader::Shader::set(const std::string& name, int& a, int& b, int& c,
                                int& d) {
  glUniform4i(glGetUniformLocation(*program_ptr, name.c_str()), a, b, c, d);
}
template <>
void forma::shader::Shader::set(const std::string& name, unsigned int& a,
                                unsigned int& b, unsigned int& c,
                                unsigned int& d) {
  glUniform4i(glGetUniformLocation(*program_ptr, name.c_str()), a, b, c, d);
}
template <>
void forma::shader::Shader::set(const std::string& name, float& a, float& b,
                                float& c, float& d) {
  glUniform4i(glGetUniformLocation(*program_ptr, name.c_str()), a, b, c, d);
}
