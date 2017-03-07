#ifndef FORMA_OBJECT_OBJECT_CLASS_HPP
#define FORMA_OBJECT_OBJECT_CLASS_HPP
#include <string>
#include <vector>
#include "../types/type_headers.hpp"
namespace forma {
  namespace object {
    enum CoordAxis { S = 0, T = 1, R = 2 };
    enum TextureWrapping {
      REPEATE = 0,
      MIRRORED_REPEAT = 1,
      CLAMP_TO_EDGE = 2,
      CLAMP_TO_BORDER = 3
    };
    class Object {
     public:
      Object();
      Object(const Object& copy_object);
      ~Object();
      void SetVertices(std::vector<triple<float, float, float>> vertices);
      void SetVertices(std::vector<float> vertices);
      void SetIndices(std::vector<int> indices);
      void Display();
      void SetShaderProgram(int index);
      void CreateObject();

      void LoadTexture(std::string file_path);

      // Texture funcitons
      void SetTextureWrapping(int axis, int wrapping);
      void SetTextureBorderColor(float red, float green, float blue,
                                 float alpha);

     private:
      void CreateVao();
      unsigned int vao, vbo, ebo, texture;
      int shader_program_index = 0;
      std::vector<triple<float, float, float>> obj_vertices;
      std::vector<int> obj_indices;
      // Texture data
      int img_width, img_height;
      unsigned char* img;
      int obj_tex_dim = 2;
    };
  }
}
#endif
