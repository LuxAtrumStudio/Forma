#ifndef FORMA_FORMA_CORE_HPP
#define FORMA_FORMA_CORE_HPP

#define FORMA_VERSION_MAJOR 0
#define FORMA_VERSION_MINOR 0
#define FORMA_VERSION_PATCH 2

namespace forma {
  void InitForma();
  void InitGlad();
  void InitGlfw();

  void TermForma();
  void TermGlad();
  void TermGlfw();

  void OpenGLVersion(int& major, int& minor);
  void GetVersion(int& major, int& minor);
  void GetVerison(int& major, int& minor, int& patch);
}  // namespace forma

#endif /* ifndef FORMA_FORMA_CORE_HPP */
