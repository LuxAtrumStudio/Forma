#include <pessum.h>
#include "../gl_headers.hpp"
#include "object.hpp"

forma::Object::Object() {}

forma::Object::Object(const Object& copy) {}

forma::Object::~Object() {
  vertex_data.clear();
  indices.clear();
}

void forma::Object::CreateObject() {
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  // VBO
  std::vector<GLfloat> vertices;
  int vertex_index = 0;
  int total = 0;
  while(vertex_index != vertex_data["vertices"].values.size()){
    for(std::map<std::string, VertexAttrib>::iterator it = vertex_data.begin(); it != vertex_data.end(); ++it){
      vertices.insert(vertices.end(), it->second.values.begin() + it->second.size * vertex_index, it->second.values.begin() + (it->second.size * vertex_index) + it->second.size);
      if(vertex_index == 0){
        total += it->second.size;
      }
    }
    vertex_index++;
  }
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
  // EBO
  if(indices.size() == 0){
    for(int i = 0; i < vertex_data["vertices"].values.size() / 3; i++){
      indices.push_back(i);
    }
  }
  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLfloat), &indices[0], GL_STATIC_DRAW);
  int count = 0;
  for(std::map<std::string, VertexAttrib>::iterator it = vertex_data.begin(); it != vertex_data.end(); ++it){
    //pessum::Log(pessum::DEBUG, "%s, %i, %i, %i
    glVertexAttribPointer(it->second.ptr, it->second.size, GL_FLOAT, GL_FALSE, total * sizeof(GLfloat), (GLvoid*)(count * sizeof(GLfloat)));
    glEnableVertexAttribArray(it->second.ptr);
    count += it->second.size;
  }
  
  glBindVertexArray(0);
}

void forma::Object::SetVertices(std::vector<float> in_vertices){
  vertex_data["vertices"].ptr = 0;
  vertex_data["vertices"].size = 3;
  vertex_data["vertices"].values = in_vertices;
}

void forma::Object::AddVertexAttrib(std::string name, int ptr, int size, std::vector<float> in_values){
  vertex_data[name].ptr = ptr;
  vertex_data[name].size = size;
  vertex_data[name].values = in_values;
}

void forma::Object::RemoveVertexAttrib(std::string name){
  if(vertex_data.find(name) != vertex_data.end()){
    vertex_data.erase(vertex_data.find(name));
  }else{
    pessum::Log(pessum::WARNING, "No vertex attribute %s exists", "forma::Object::RemoveVertexAttrib", name.c_str());
  }
}

void forma::Object::SetIndices(std::vector<int> in_indices){
  indices = in_indices;
}

void forma::Object::SetShaderProgram(Shader in_shader_program){
  shader_program = in_shader_program;
}

void forma::Object::Display(){
  if(shader_program.created == true){
    glUseProgram(shader_program());
  }else{
    pessum::Log(pessum::WARNING, "Shader has not been set", "forma::Object::Display");
    shader_program.AddShader(FORMA_VERTEX_SHADER, "");
    shader_program.AddShader(FORMA_FRAGMENT_SHADER, "");
    shader_program.CreateProgram();
    glUseProgram(shader_program());
  }
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  //glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
}
