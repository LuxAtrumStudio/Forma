#version 450 core

out vec4 FragColor;
in vec3 out_color;

void main()
{
  // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
  FragColor = vec4(out_color, 1.0f);
}
