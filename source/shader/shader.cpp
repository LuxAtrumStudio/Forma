#include "shader.hpp"

#include <array>
#include <fstream>
#include <memory>
#include <string>

#include <pessum/pessum.hpp>

#include "../gl_headers.hpp"

forma::shader::Shader::Shader() {}

forma::shader::Shader::Shader(const Shader& copy) {}

forma::shader::Shader::~Shader() {}

void forma::shader::Shader::AddShader(int shader, std::string shader_path) {
  std::string shader_str;
  if (shader_path != "") {
    shader_str = GetShaderString(shader_path);
  }
  if (shader_str == std::string()) {
    shader_str = GetDefaultShader(shader);
  }
  unsigned int shader_uint = 0;
  if (shader == VERTEX) {
    shader_uint = glCreateShader(GL_VERTEX_SHADER);
  } else if (shader == GEOMETRY) {
    shader_uint = glCreateShader(GL_GEOMETRY_SHADER);
  } else if (shader == FRAGMENT) {
    shader_uint = glCreateShader(GL_FRAGMENT_SHADER);
  }
  const char* shader_source = shader_str.c_str();
  glShaderSource(shader_uint, 1, &shader_source, NULL);
  glCompileShader(shader_uint);
  int status;
  glGetShaderiv(shader_uint, GL_COMPILE_STATUS, &status);
  if (status == false) {
    int info_length;
    glGetShaderiv(shader_uint, GL_INFO_LOG_LENGTH, &info_length);
    std::vector<char> info_log(info_length + 1);
    glGetShaderInfoLog(shader_uint, info_length, NULL, &info_log[0]);
    std::string info_str(info_log.begin(), info_log.end());
    std::string shader_type = "";
    if (shader == VERTEX) {
      shader_type = "SHADER::FRAGMENT";
    } else if (shader == GEOMETRY) {
      shader_type = "SHADER::GEOMETRY";
    } else if (shader == FRAGMENT) {
      shader_type = "SHADER::FRAGMENT";
    }
    pessum::Log(pessum::ERROR, "%s:%s", "forma::Shader::AddShader",
                shader_type.c_str(), info_str.c_str());
  } else {
    shaders[shader] = std::make_pair(true, shader_uint);
  }
}

void forma::shader::Shader::CreateProgram() {
  if (shaders[VERTEX].first == false) {
    pessum::Log(pessum::WARNING,
                "Shader program requires defined vertex shader",
                "forma::shader::Shader::CreateProgram");
    AddShader(VERTEX, "");
  }
  if (shaders[FRAGMENT].first == false) {
    pessum::Log(pessum::WARNING,
                "Shader program requires defined fragment shader",
                "forma::shader::Shader::CreateProgram");
    AddShader(FRAGMENT, "");
  }
  program = std::make_shared<unsigned int>(glCreateProgram());
  for (int i = 0; i < 3; i++) {
    if (shaders[i].first == true) {
      glAttachShader(*program, shaders[i].second);
    }
  }
  glLinkProgram(*program);

  GLint success, log_length;
  glGetProgramiv(*program, GL_LINK_STATUS, &success);
  if (success == false) {
    glGetProgramiv(*program, GL_INFO_LOG_LENGTH, &log_length);
    std::vector<char> info_log(log_length + 1);
    glGetProgramInfoLog(*program, log_length, NULL, &info_log[0]);
    std::string info_str(info_log.begin(), info_log.end());
    pessum::Log(pessum::ERROR, "SHADER::PROGRAM:%s",
                "forma::shader::Shader::CreateProgram", info_str.c_str());
    program = NULL;
  }
}

void forma::shader::Shader::AddUniformi(std::string name, int v0) {
  int uniform_location = GetUniformLocation(name);
  if (uniform_location == -1) {
    return;
  }
  glUseProgram(*program);
  glUniform1i(uniform_location, v0);
}

void forma::shader::Shader::AddUniformi(std::string name, int v0, int v1) {
  int uniform_location = GetUniformLocation(name);
  if (uniform_location == -1) {
    return;
  }
  glUseProgram(*program);
  glUniform2i(uniform_location, v0, v1);
}

void forma::shader::Shader::AddUniformi(std::string name, int v0, int v1,
                                        int v2) {
  int uniform_location = GetUniformLocation(name);
  if (uniform_location == -1) {
    return;
  }
  glUseProgram(*program);
  glUniform3i(uniform_location, v0, v1, v2);
}

void forma::shader::Shader::AddUniformi(std::string name, int v0, int v1,
                                        int v2, int v3) {
  int uniform_location = GetUniformLocation(name);
  if (uniform_location == -1) {
    return;
  }
  glUseProgram(*program);
  glUniform4i(uniform_location, v0, v1, v2, v3);
}

void forma::shader::Shader::AddUniformui(std::string name, unsigned int v0) {
  int uniform_location = GetUniformLocation(name);
  if (uniform_location == -1) {
    return;
  }
  glUseProgram(*program);
  glUniform1ui(uniform_location, v0);
}

void forma::shader::Shader::AddUniformui(std::string name, unsigned int v0,
                                         unsigned int v1) {
  int uniform_location = GetUniformLocation(name);
  if (uniform_location == -1) {
    return;
  }
  glUseProgram(*program);
  glUniform2i(uniform_location, v0, v1);
}

void forma::shader::Shader::AddUniformui(std::string name, unsigned int v0,
                                         unsigned int v1, unsigned int v2) {
  int uniform_location = GetUniformLocation(name);
  if (uniform_location == -1) {
    return;
  }
  glUseProgram(*program);
  glUniform3ui(uniform_location, v0, v1, v2);
}

void forma::shader::Shader::AddUniformui(std::string name, unsigned int v0,
                                         unsigned int v1, unsigned int v2,
                                         unsigned int v3) {
  int uniform_location = GetUniformLocation(name);
  if (uniform_location == -1) {
    return;
  }
  glUseProgram(*program);
  glUniform4ui(uniform_location, v0, v1, v2, v3);
}

void forma::shader::Shader::AddUniformf(std::string name, float v0) {
  int uniform_location = GetUniformLocation(name);
  if (uniform_location == -1) {
    return;
  }
  glUseProgram(*program);
  glUniform1f(uniform_location, v0);
}

void forma::shader::Shader::AddUniformf(std::string name, float v0, float v1) {
  int uniform_location = GetUniformLocation(name);
  if (uniform_location == -1) {
    return;
  }
  glUseProgram(*program);
  glUniform2f(uniform_location, v0, v1);
}

void forma::shader::Shader::AddUniformf(std::string name, float v0, float v1,
                                        float v2) {
  int uniform_location = GetUniformLocation(name);
  if (uniform_location == -1) {
    return;
  }
  glUseProgram(*program);
  glUniform3f(uniform_location, v0, v1, v2);
}

void forma::shader::Shader::AddUniformf(std::string name, float v0, float v1,
                                        float v2, float v3) {
  int uniform_location = GetUniformLocation(name);
  if (uniform_location == -1) {
    return;
  }
  glUseProgram(*program);
  glUniform4f(uniform_location, v0, v1, v2, v3);
}

unsigned int forma::shader::Shader::operator()() {
  if (program != NULL) {
    return (*program);
  } else {
    pessum::Log(pessum::WARNING, "Shader program not exist",
                "forma::shader::Shader::operator()");
    return (0);
  }
}

std::string forma::shader::Shader::GetShaderString(std::string shader_path) {
  std::ifstream load(shader_path.c_str());
  std::string file;
  if (load.is_open()) {
    std::string line;
    while (getline(load, line)) {
      file += line + "\n";
    }
    load.close();
  } else {
    pessum::Log(pessum::WARNING, "Failed to open shader \"%s\"",
                "forma::shader::Shader::GetShaderString", shader_path.c_str());
  }
  return file;
}

std::string forma::shader::Shader::GetDefaultShader(int shader) {
  std::string shader_str;
  if (shader == VERTEX) {
    shader_str =
        "#version 450 core\n"
        "layout(location = 0) in vec3 position;\n"
        "void main() {\n"
        "  gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n"
        "}";
  } else if (shader == GEOMETRY) {
    shader_str =
        "#version 330 core\n"
        "layout(points) in;\n"
        "layout(line_strip, max_vertices = 2) out;\n"
        "void main() {\n"
        "  gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0);\n"
        "  EmitVertex();\n"
        "  gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.0, 0.0, 0.0);\n"
        "  EmitVertex();\n"
        "  EndPrimitive();\n"
        "}";
  } else if (shader == FRAGMENT) {
    shader_str =
        "#version 450 core\n"
        "out vec4 color;\n"
        "void main() {"
        "  color = vec4(1.0f, 1.0f, 1.0f, 1.0f);"
        "}";
  }
  return shader_str;
}

int forma::shader::Shader::GetUniformLocation(std::string name) {
  int uniform_location = glGetUniformLocation(*program, name.c_str());
  if (uniform_location == -1) {
    pessum::Log(pessum::WARNING,
                "OpenGL could not find \"%s\" uniform in the shader program",
                "forma::shader::AddUniform", name.c_str());
  }
  return (uniform_location);
}
