#include <pessum.h>
#include "../gl_headers.hpp"
#include "object.hpp"

forma::Object::Object() {}

forma::Object::Object(const Object& copy) {}

forma::Object::~Object() {}

void forma::Object::CreateObject() {
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  // VBO
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
  // EBO
  if(indices.size() == 0){
    for(int i = 0; i < vertices.size() / 3; i++){
      indices.push_back(i);
    }
  }
  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLfloat), &indices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  
  glBindVertexArray(0);
}

void forma::Object::SetVertices(std::vector<float> in_vertices){
  vertices = in_vertices;
}

void forma::Object::SetIndices(std::vector<int> in_indices){
  indices = in_indices;
}

void forma::Object::SetShaderProgram(Shader in_shader_program){
  shader_program = in_shader_program;
}

void forma::Object::Display(){
  glUseProgram(shader_program());
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  //glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
}
