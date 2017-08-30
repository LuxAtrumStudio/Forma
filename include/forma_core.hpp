#ifndef FORMA_FORMA_CORE_HPP
#define FORMA_FORMA_CORE_HPP

#define FORMA_VERSION_MAJOR 0
#define FORMA_VERSION_MINOR 0

namespace forma {
  void InitForma();
  void InitGlad();
  void InitGlfw();

  void TermForma();
  void TermGlad();
  void TermGlfw();

  bool FormaInit();
  bool GladInit();
  bool GlfwInit();

  void OpenGLVersion(int& major, int& minor);
  void GLFWVersion(int& major, int& minor);
  void FormaVersion(int& major, int& minor);
}  // namespace forma

#endif /* ifndef FORMA_FORMA_CORE_HPP */
