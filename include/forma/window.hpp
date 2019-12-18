#ifndef WINDOW_HPP_EBAIFE1A
#define WINDOW_HPP_EBAIFE1A

#include <cstdlib>
#include <string>

#include "image.hpp"
#include "math.hpp"

namespace forma {
  namespace window {
    enum Flags {
      RESIZABLE = 1L << 0,
      VISIBLE = 1L << 1,
      DECORATED = 1L << 2,
      FOCUSED = 1L << 3,
      AUTO_ICONIFY = 1L << 4,
      FLOATING = 1L << 5,
      MAXIMIZED = 1L << 6,
      CENTER_CURSOR = 1L << 7,
      TRANSPARENT_FRAMEBUFFER = 1L << 8,
      FOCUS_ON_SHOW = 1L << 9,
      SCALE_TO_MONITOR = 1L << 10,
      FULLSCREEN = 1L << 11,
    };
    bool create(std::uint32_t flags = FULLSCREEN | VISIBLE | DECORATED |
                                      FOCUSED | AUTO_ICONIFY | CENTER_CURSOR |
                                      FOCUS_ON_SHOW);
    bool create(const std::string& title,
                std::uint32_t flags = FULLSCREEN | VISIBLE | DECORATED |
                                      FOCUSED | AUTO_ICONIFY | CENTER_CURSOR |
                                      FOCUS_ON_SHOW);
    bool create(const uvec2& dim,
                std::uint32_t flags = RESIZABLE | VISIBLE | DECORATED |
                                      FOCUSED | AUTO_ICONIFY | CENTER_CURSOR |
                                      FOCUS_ON_SHOW);
    bool create(const std::string& title, const uvec2& dim,
                std::uint32_t flags = RESIZABLE | VISIBLE | DECORATED |
                                      FOCUSED | AUTO_ICONIFY | CENTER_CURSOR |
                                      FOCUS_ON_SHOW);
    bool create(const uvec2& dim, const std::string& title,
                std::uint32_t flags = RESIZABLE | VISIBLE | DECORATED |
                                      FOCUSED | AUTO_ICONIFY | CENTER_CURSOR |
                                      FOCUS_ON_SHOW);
    bool should_close();
    void update();
    bool destroy();

    bool is_fullscreen();
    bool is_windowed();
    bool is_iconified();
    bool is_maximized();
    bool is_hidden();
    bool is_visible();
    bool is_focused();
    float get_opacity();
    uvec2 get_size();
    uvec2 get_framebuffer_size();
    vec2 get_content_scale();

    void toggle_fullscreen();
    void set_fullscreen(bool setting = true);
    void toggle_windowed();
    void set_windowed(bool setting = true);
    void toggle_iconfification();
    void set_iconification(bool setting = true);
    void toggle_maximization();
    void set_maximization(bool setting = true);
    void toggle_visibility();
    void set_visibility(bool setting = true);
    void toggle_focus();
    void set_focus(bool setting = true);
    void toggle_decoration();
    void set_decoration(bool setting = true);
    void toggle_resizability();
    void set_resizability(bool setting = true);
    void toggle_floating();
    void set_floating(bool setting = true);
    void set_opacity(float val = 1.0f);

    void set_size(const uvec2& size);
    void set_size_limit(const uvec2& min, const uvec2& max);
    void set_aspect_ratio(const uvec2& ratio);
    void set_pos(const uvec2& pos);
    void set_title(const std::string& title);
    void add_icon(const image::Image& img);
    void clear_icons();

    void request_attention();

  }  // namespace window
}  // namespace forma

#endif /* end of include guard: WINDOW_HPP_EBAIFE1A */
