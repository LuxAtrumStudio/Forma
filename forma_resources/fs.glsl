#version 450 core

in vec3 vertex_color;

out vec4 color;

void main()
{
  color = vec4(vertex_color, 1.0f);
  //color = vec4(1.0, 1.0, 1.0, 1.0);
}
