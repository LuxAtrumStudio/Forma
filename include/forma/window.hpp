#ifndef WINDOW_HPP_EBAIFE1A
#define WINDOW_HPP_EBAIFE1A

namespace forma {
  namespace window {
    bool Create(const std::size_t& width, const std::size_t& height);
    bool Destroy();

    void GetFullscreen();

    void SetFullscreen();
    void SetFullscreen(bool setting);
    void SetSize(const std::size_t& width, const std::size_t& height);
    void SetAspectRatio(const std::size_t& width, const std::size_t& height);
    void SetPos(const std::size_t& x, const std::size_t& y);
    template <typename CharT>
    void SetTitle(const std::basic_string<CharT>& title);
  }  // namespace window
}  // namespace forma

#endif /* end of include guard: WINDOW_HPP_EBAIFE1A */
