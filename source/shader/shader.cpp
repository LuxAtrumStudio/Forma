#include "shader/shader.hpp"

#include <array>
#include <fstream>
#include <string>

#include "gl.hpp"
#include "log/log.hpp"

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
    log::Log(log::WARNING, "Could not open vertex shader at \"%s\"",
             "forma::shader::Shader::VertexShader", shader.c_str());
  }
}

void forma::shader::Shader::FragmentShader(std::string shader) {
  if (FileExists(shader)) {
    shaders_[1] = shader;
  } else {
    log::Log(log::WARNING, "Could not open fragment shader at \"%s\"",
             "forma::shader::Shader::FragmentShader", shader.c_str());
  }
}

void forma::shader::Shader::CompileShader() {
  unsigned int vertex = LoadShader(shaders_[0], 0);
  unsigned int fragment = LoadShader(shaders_[1], 1);
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
  unsigned int shader_id = 0;
  if (shader == 0) {
    shader_id = glCreateShader(GL_VERTEX_SHADER);
  } else if (shader == 1) {
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
  } else {
    if (shader == 0) {
      log::Log(log::ERROR, "Vertex shader not defined",
               "forma::shader::Shader::LoadShader");
    }
  }
  return shader_id;
}
