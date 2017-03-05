#include <pessum.h>
#include <string>
#include <vector>
#include "../gl_headers.hpp"
#include "../types/type_headers.hpp"
#include "object_class.hpp"
#include "shader.hpp"

forma::object::Object::Object() {}

forma::object::Object::Object(const Object& copy_object) {}

forma::object::Object::~Object() {
  obj_vertices.clear();
  obj_indices.clear();
}

void forma::object::Object::SetVertices(
    std::vector<triple<float, float, float>> vertices) {
  obj_vertices = vertices;
}

void forma::object::Object::SetVertices(std::vector<float> vertices) {
  if (vertices.size() % 3 != 0) {
    pessum::logging::Log("warning", "Invalid number of vertex data point",
                         "forma/object/object_class/SetVertices(2)");
    while (vertices.size() % 3 != 0) {
      vertices.push_back(0.0);
    }
  }
  for (int i = 0; i < vertices.size(); i += 3) {
    obj_vertices.push_back(
        make_triple(vertices[i], vertices[i + 1], vertices[i + 2]));
  }
}

void forma::object::Object::SetIndices(std::vector<int> indices) {
  obj_indices = indices;
}

void forma::object::Object::Display() {
  if (shaders.size() == 0) {
    CreateShader();
  }
  if (shader_program_index >= shaders.size()) {
    pessum::logging::Log("warning", "No shader initialized with index: " +
                                        std::to_string(shader_program_index),
                         "forma/object/object_class/Display");
    shader_program_index = 0;
  }
  shaders[shader_program_index].UseShader();
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, obj_indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void forma::object::Object::SetShaderProgram(int index) {
  shader_program_index = index;
}

void forma::object::Object::CreateObject() { CreateVao(); }

void forma::object::Object::CreateVao() {
  std::vector<float> gl_vertices;
  for (int i = 0; i < obj_vertices.size(); i++) {
    gl_vertices.push_back(obj_vertices[i].first);
    gl_vertices.push_back(obj_vertices[i].second);
    gl_vertices.push_back(obj_vertices[i].third);
  }
  if (obj_indices.size() == 0) {
    for (int i = 0; i < obj_vertices.size(); i++) {
      obj_indices.push_back(i);
    }
  }
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, gl_vertices.size() * sizeof(float),
               &gl_vertices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj_indices.size() * sizeof(int),
               &obj_indices[0], GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                        (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
