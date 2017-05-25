#include "../gl_headers.hpp"
#include <string>
#include <vector>
#include <pessum.h>
#include "shader.hpp"
#include <memory>
#include <fstream>

forma::Shader::Shader(){
}

forma::Shader::Shader(const Shader& copy){
  vs = copy.vs;
  gs = copy.gs;
  ts = copy.gs;
  fs = copy.fs;
  shader_program = copy.shader_program;
  vertex_shader = copy.vertex_shader;
  geometry_shader = copy.geometry_shader;
  tesselation_shader = copy.tesselation_shader;
  fragment_shader = copy.fragment_shader;
}

forma::Shader::~Shader(){
  if(shader_program.use_count() == 1){
    if(vs == true){
      glDeleteShader(vertex_shader);
    }
    if(gs == true){
      glDeleteShader(geometry_shader);
    }
    if(ts == true){
      glDeleteShader(tesselation_shader);
    }
    if(fs == true){
      glDeleteShader(fragment_shader);
    }
    glDeleteProgram(*shader_program);
  }
  shader_program = NULL;
}

void forma::Shader::AddShader(int shader, std::string shader_path){
  std::string shader_string = "";
  
  std::ifstream load(shader_path.c_str());
  if(load.is_open()){
    std::string line = "";
   while(getline(load, line)){
    shader_string += line + '\n';
   }
   load.close();
  }else{
    pessum::Log(pessum::WARNING, "Invalid shader path \"%s\"", "forma::Shader::AddShader", shader_path.c_str());
  }
  GLuint shader_uint;
  if(shader == FORMA_VERTEX_SHADER){
    shader_uint = glCreateShader(GL_VERTEX_SHADER);
    if(shader_string == ""){
      shader_string = "#version 450 core\n"
                      "layout(location = 0) in vec3 position;\n"
                      "void main() {"
                      " gl_Position = vec4(position.x, position.y, position.z, 1.0f);"
                      "}";

    }
  }else if(shader == FORMA_FRAGMENT_SHADER){
    shader_uint = glCreateShader(GL_FRAGMENT_SHADER);
    if(shader_string == ""){
      shader_string = "#version 450 core\n"
                      "out vec4 color;\n"
                      "void main() {"
                      "color = vec4(1.0f, 1.0f, 1.0f, 1.0f);"
                      "}";
    }
  }
  const char* shader_source = shader_string.c_str();
  glShaderSource(shader_uint, 1, &shader_source, NULL);
  glCompileShader(shader_uint);
  GLint success, log_length;
  glGetShaderiv(shader_uint, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderiv(shader_uint, GL_INFO_LOG_LENGTH, &log_length);
    std::vector<char> info_log(log_length + 1);
    glGetShaderInfoLog(shader_uint, log_length, NULL, &info_log[0]);
    std::string info_str (info_log.begin(), info_log.end());
    std::string shader_type = "";
    if(shader == FORMA_VERTEX_SHADER){
      shader_type = "Vertex Shader";
    }else if(shader == FORMA_FRAGMENT_SHADER){
      shader_type = "Fragment Shader";
    }
    pessum::Log(pessum::ERROR, "%s:%s", "forma::Shader::AddShader", shader_type.c_str(), info_str.c_str());
  }else{
    if(shader == FORMA_VERTEX_SHADER){
      vertex_shader = shader_uint;
      vs = true;
    }else if(shader == FORMA_FRAGMENT_SHADER){
      fragment_shader = shader_uint;
      fs = true;
    }
  }
}

void forma::Shader::CreateProgram(){
  if(vs == false || fs == false){
    pessum::Log(pessum::WARNING, "Shader program must define vetex and fragment shaders", "forma::Shader::CreateProgram");
  }else{
    shader_program = std::make_shared<GLuint>(glCreateProgram());
    if(vs == true){
      glAttachShader(*shader_program, vertex_shader);
    }
    if(gs == true){
      glAttachShader(*shader_program, geometry_shader);
    }
    if(ts == true){
      glAttachShader(*shader_program, tesselation_shader);
    }
    if(fs == true){
      glAttachShader(*shader_program, fragment_shader);
    }
    glLinkProgram(*shader_program);
    
    GLint success, log_length;
    glGetProgramiv(*shader_program, GL_LINK_STATUS, &success);
    if(!success){
      glGetProgramiv(*shader_program, GL_INFO_LOG_LENGTH, &log_length);
      std::vector<char> info_log(log_length + 1);
      glGetProgramInfoLog(*shader_program, log_length, NULL, &info_log[0]);
      std::string info_str(info_log.begin(), info_log.end());
      pessum::Log(pessum::ERROR, "%s", "forma::Shader::CreateProgram", info_str.c_str());
    }
  }
}
