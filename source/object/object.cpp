#include "object.hpp"

#include <vector>

#include "../gl_headers.hpp"
#include "vertex_attr.hpp"

forma::object::Object::Object() {}

forma::object::Object::Object(const Object& copy) {}

forma::object::Object::~Object() {}

void forma::object::Object::CreateObject() { GenerateObject(); }

void forma::object::Object::SetVertices(std::vector<float> vertices) {
  vertex_data["vertices"] = VertexAttr(0, 3, vertices);
}

void forma::object::Object::SetIndices(std::vector<int> indices_) {
  indices = indices_;
}

void forma::object::Object::AddVertexAttr(std::string name, int ptr, int size,
                                          std::vector<float> data) {
  vertex_data[name] = VertexAttr(ptr, size, data);
}

void forma::object::Object::RemoveVertexAttr(std::string name) {
  if (vertex_data.find(name) != vertex_data.end()) {
    vertex_data.erase(vertex_data.find(name));
  }
}

void forma::object::Object::SetShaderProgram(shader::Shader program) {
  shader_program = program;
}

void forma::object::Object::Display() {
  if (shader_program.IsValid() == true) {
    glUseProgram(shader_program());
  }
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  // glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
}

void forma::object::Object::GenerateObject() {
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  // VBO
  std::vector<float> vertices;
  int vertex_index = 0;
  int total = 0;
  while (vertex_index != vertex_data["vertices"].data.size()) {
    for (std::map<std::string, VertexAttr>::iterator it = vertex_data.begin();
         it != vertex_data.end(); ++it) {
      vertices.insert(vertices.end(),
                      it->second.data.begin() + it->second.size * vertex_index,
                      it->second.data.begin() +
                          (it->second.size * vertex_index) + it->second.size);
      if (vertex_index == 0) {
        total += it->second.size;
      }
    }
    vertex_index++;
  }
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0],
               GL_STATIC_DRAW);
  // EBO
  if (indices.size() == 0) {
    for (int i = 0; i < vertex_data["vertices"].data.size() / 3; i++) {
      indices.push_back(i);
    }
  }
  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float),
               &indices[0], GL_STATIC_DRAW);
  int count = 0;
  for (std::map<std::string, VertexAttr>::iterator it = vertex_data.begin();
       it != vertex_data.end(); ++it) {
    // pessum::Log(pessum::DEBUG, "%s, %i, %i, %i
    glVertexAttribPointer(it->second.position, it->second.size, GL_FLOAT,
                          GL_FALSE, total * sizeof(float),
                          (GLvoid*)(count * sizeof(float)));
    glEnableVertexAttribArray(it->second.position);
    count += it->second.size;
  }

  glBindVertexArray(0);
}
