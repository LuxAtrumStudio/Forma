#ifndef FORMA_FRAMEWOK_GL_SETTINGS_HPP
#define FORMA_FRAMEWOK_GL_SETTINGS_HPP
namespace forma {
  namespace framework {
    enum PolygonFaces { FRONT = 0, BACK = 1, FRONT_AND_BACK = 2 };
    enum PolygonMode { POINT = 0, LINE = 1, FILL = 2 };
    void PolygonMode(int face, int mode);
  }
}
#endif
