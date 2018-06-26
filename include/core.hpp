#ifndef FORMA_CORE_HPP_
#define FORMA_CORE_HPP_

#define FORMA_VERSION_MAJOR 0
#define FORMA_VERSION_MINOR 0

namespace forma {
  bool InitForma();
  bool InitGlad();
  bool InitGlfw();

  bool TermForma();
  bool TermGlad();
  bool TermGlfw();

  void FormaVersion(int& major, int& minor);
  void GLFWVersion(int& major, int& minor);
  void OpenGLVersion(int& major, int& minor);
} // namespace forma

#endif  // FORMA_CORE_HPP_
