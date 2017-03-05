#include <pessum.h>
#include <fstream>
#include <string>
#include "../gl_headers.hpp"
#include "../types/type_headers.hpp"
#include "shader_class.hpp"

forma::object::Shader::Shader() {}

forma::object::Shader::Shader(std::string vertex_shader,
                              std::string fragment_shader) {
  shader_file_path = std::make_pair(vertex_shader, fragment_shader);
}

forma::object::Shader::Shader(const Shader& copy_shader) {
  shader_program = copy_shader.shader_program;
  shader_file_path = copy_shader.shader_file_path;
}

forma::object::Shader::~Shader() { shader_program = 0; }

void forma::object::Shader::CreateShader() {
  std::string vertex_shader_string = ReadShaderFile(shader_file_path.first);
  std::string fragment_shader_string = ReadShaderFile(shader_file_path.second);
  if (vertex_shader_string == "") {
    vertex_shader_string =
        "#version 330 core\n layout(location = 0) in vec3 position;\n void "
        "main() { gl_Position = vec4(position.x, position.y, position.z, 1.0); "
        "}";
  }
  if (fragment_shader_string == "") {
    fragment_shader_string =
        "#version 330 core\n out vec4 color;\n void main() { color = "
        "vec4(1.0f, 1.0f, 1.0f, 1.0f); }";
  }
  const char* vertex_shader_source = vertex_shader_string.c_str();
  const char* fragment_shader_source = fragment_shader_string.c_str();
  unsigned int vertex_shader, fragment_shader;
  int result;
  int log_length;
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);

  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);
  if (!result) {
    std::vector<char> info_log(log_length + 1);
    glGetShaderInfoLog(vertex_shader, log_length, NULL, &info_log[0]);
    std::string error_log(info_log.begin(), info_log.end());
    pessum::logging::Log("error",
                         "Failed to compile vertex shader: " + error_log,
                         "forma/object/shader_class/CreateShader");
  }

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_length);
  if (!result) {
    std::vector<char> info_log(log_length + 1);
    glGetShaderInfoLog(fragment_shader, log_length, NULL, &info_log[0]);
    std::string error_log(info_log.begin(), info_log.end());
    pessum::logging::Log("error",
                         "Failed to compile fragment shader: " + error_log,
                         "forma/object/shader_class/CreateShader");
  }

  shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);

  glGetProgramiv(shader_program, GL_LINK_STATUS, &result);
  glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &log_length);
  if (!result) {
    std::vector<char> info_log(log_length + 1);
    glGetProgramInfoLog(shader_program, log_length, NULL, &info_log[0]);
    std::string error_log(info_log.begin(), info_log.end());
    pessum::logging::Log("error",
                         "Failed to compile shader program: " + error_log,
                         "forma/object/shader_class/CreateShader");
  }
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

void forma::object::Shader::DeleteShader() {
  if (shader_program != 0) {
    glDeleteProgram(shader_program);
    shader_program = 0;
  }
}

void forma::object::Shader::SetShaderFile(int shader, std::string file_path) {
  if (shader == 0) {
    shader_file_path.first = file_path;
  } else if (shader == 1) {
    shader_file_path.second = file_path;
  } else {
    pessum::logging::Log("warning",
                         "No shader binding for " + std::to_string(shader),
                         "forma/object/shader_class/SetShaderFile");
  }
}

unsigned int forma::object::Shader::GetShaderProgram() {
  return (shader_program);
}

void forma::object::Shader::UseShader() { glUseProgram(shader_program); }

std::string forma::object::Shader::ReadShaderFile(std::string file_path) {
  std::string shader_contents = "";
  std::ifstream shader_file(file_path.c_str());
  if (shader_file.is_open()) {
    std::string line = "";
    while (getline(shader_file, line)) {
      shader_contents += line + "\n";
    }
    shader_file.close();
  } else {
    pessum::logging::Log("warning", "Failed to open shader file: " + file_path,
                         "forma/object/shader_class/ReadShaderFile");
  }
  return (shader_contents);
}
