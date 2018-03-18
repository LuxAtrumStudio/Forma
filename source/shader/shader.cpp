#include "shader/shader.hpp"

#include <array>
#include <fstream>
#include <string>
#include <vector>

#include "gl.hpp"
#include "log/logger.hpp"

forma::shader::Shader::Shader() {}

forma::shader::Shader::Shader(const Shader& copy) {
  shaders_ = copy.shaders_;
  id_ = copy.id_;
}

forma::shader::Shader::~Shader() {
  if (id_.use_count() == 1) {
    glDeleteProgram(*id_);
  }
  id_ = NULL;
}

void forma::shader::Shader::VertexShader(std::string shader) {
  if (FileExists(shader)) {
    shaders_[0] = shader;
  } else {
    logging::Warning("shader/shader.cpp",
                     "forma::shader::Shader::VertexShader(std::string)",
                     "Could not open vertex shader at \"%s\"", shader.c_str());
  }
}

void forma::shader::Shader::FragmentShader(std::string shader) {
  if (FileExists(shader)) {
    shaders_[1] = shader;
  } else {
    logging::Warning("shader/shader.cpp",
                     "forma::shader::Shader::FragmentShader(std::string)",
                     "Could not open fragment shader at \"%s\"",
                     shader.c_str());
  }
}

void forma::shader::Shader::CompileShader() {
  unsigned int vertex = LoadShader(shaders_[0], 0);
  unsigned int fragment = LoadShader(shaders_[1], 1);
  id_ = std::make_shared<unsigned int>(glCreateProgram());
  glAttachShader(*id_, vertex);
  glAttachShader(*id_, fragment);
  glLinkProgram(*id_);
  int status;
  glGetProgramiv(*id_, GL_LINK_STATUS, &status);
  if (status == 0) {
    int log_length;
    glGetProgramiv(*id_, GL_INFO_LOG_LENGTH, &log_length);
    std::vector<char> info_log(log_length + 1);
    glGetProgramInfoLog(*id_, log_length, NULL, &info_log[0]);
    std::string info_str(info_log.begin(), info_log.end());
    logging::Fatal("shader/shader.cpp",
                   "forma::shader::Shader::CompileShader()", "%s",
                   info_str.c_str());
    glDeleteProgram(*id_);
    id_ = NULL;
  }
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void forma::shader::Shader::DestroyShader() {
  if (id_.use_count() == 1) {
    glDeleteProgram(*id_);
  }
  id_ = NULL;
}

bool forma::shader::Shader::IsValid() {
  if (id_ != NULL) {
    return true;
  } else {
    return false;
  }
}

void forma::shader::Shader::Use() {
  if (id_ != NULL) {
    glUseProgram(*id_);
  } else {
    logging::Warning("shader/shader.cpp", "forma::shader::Shader::Use()",
                     "Shader program not defined");
  }
}

std::shared_ptr<forma::shader::Shader> forma::shader::Shader::GetPtr() {
  return std::make_shared<forma::shader::Shader>(*this);
}

void forma::shader::Shader::Uniform1f(const std::string& name, float v0) {
  glUniform1f(glGetUniformLocation(*id_, name.c_str()), v0);
}

void forma::shader::Shader::Uniform2f(const std::string& name, float v0,
                                      float v1) {
  glUniform2f(glGetUniformLocation(*id_, name.c_str()), v0, v1);
}

void forma::shader::Shader::Uniform3f(const std::string& name, float v0,
                                      float v1, float v2) {
  glUniform3f(glGetUniformLocation(*id_, name.c_str()), v0, v1, v2);
}

void forma::shader::Shader::Uniform4f(const std::string& name, float v0,
                                      float v1, float v2, float v3) {
  glUniform4f(glGetUniformLocation(*id_, name.c_str()), v0, v1, v2, v3);
}

void forma::shader::Shader::Uniform1i(const std::string& name, int v0) {
  glUniform1i(glGetUniformLocation(*id_, name.c_str()), v0);
}

void forma::shader::Shader::Uniform2i(const std::string& name, int v0, int v1) {
  glUniform2i(glGetUniformLocation(*id_, name.c_str()), v0, v1);
}

void forma::shader::Shader::Uniform3i(const std::string& name, int v0, int v1,
                                      int v2) {
  glUniform3i(glGetUniformLocation(*id_, name.c_str()), v0, v1, v2);
}

void forma::shader::Shader::Uniform4i(const std::string& name, int v0, int v1,
                                      int v2, int v3) {
  glUniform4i(glGetUniformLocation(*id_, name.c_str()), v0, v1, v2, v3);
}

void forma::shader::Shader::Uniform1ui(const std::string& name,
                                       unsigned int v0) {
  glUniform1ui(glGetUniformLocation(*id_, name.c_str()), v0);
}

void forma::shader::Shader::Uniform2ui(const std::string& name, unsigned int v0,
                                       unsigned int v1) {
  glUniform2ui(glGetUniformLocation(*id_, name.c_str()), v0, v1);
}

void forma::shader::Shader::Uniform3ui(const std::string& name, unsigned int v0,
                                       unsigned int v1, unsigned int v2) {
  glUniform3ui(glGetUniformLocation(*id_, name.c_str()), v0, v1, v2);
}

void forma::shader::Shader::Uniform4ui(const std::string& name, unsigned int v0,
                                       unsigned int v1, unsigned int v2,
                                       unsigned int v3) {
  glUniform4ui(glGetUniformLocation(*id_, name.c_str()), v0, v1, v2, v3);
}

bool forma::shader::Shader::FileExists(std::string name) {
  if (FILE* file = fopen(name.c_str(), "r")) {
    fclose(file);
    return true;
  } else {
    return false;
  }
}

unsigned int forma::shader::Shader::LoadShader(std::string name,
                                               unsigned int shader) {
  unsigned int shader_id;
  std::string shader_name;
  if (shader == 0) {
    shader_name = "Vertex";
    shader_id = glCreateShader(GL_VERTEX_SHADER);
  } else if (shader == 1) {
    shader_name = "Fragment";
    shader_id = glCreateShader(GL_FRAGMENT_SHADER);
  }
  std::string shader_str;
  std::ifstream file(name.c_str());
  if (file.is_open() == true) {
    file.seekg(0, std::ios::end);
    shader_str.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    shader_str.assign((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
    file.close();
    const char* shader_source = shader_str.c_str();
    glShaderSource(shader_id, 1, &shader_source, NULL);
    glCompileShader(shader_id);
    int status;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
    if (status == 0) {
      int info_length;
      glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_length);
      std::vector<char> info_log(info_length + 1);
      glGetShaderInfoLog(shader_id, info_length, NULL, &info_log[0]);
      std::string info_string(info_log.begin(), info_log.end());
      logging::Fatal("shader/shader.cpp", shader_name, "%s",
                     info_string.c_str());
      glDeleteShader(shader_id);
      shader_id = 0;
    }
  } else {
    logging::Error(
        "shader/shader.cpp",
        "forma::shader::Shader::LoadShader(std::string, unsigned int)",
        "%s shader not defined", shader_name.c_str());
  }
  return shader_id;
}
