#include "forma/window.hpp"

#include <cstdlib>
#include <string>

#include "forma/image.hpp"
#include "forma/log.hpp"
#include "forma/math.hpp"
#include "gl.hpp"

static GLFWwindow* glfw_window;
static std::string window_title;

void window_hints(const std::uint32_t flags) {
  glfwWindowHint(GLFW_RESIZABLE, ((flags & forma::window::RESIZABLE) ==
                                  forma::window::RESIZABLE)
                                     ? GLFW_TRUE
                                     : GLFW_FALSE);
  glfwWindowHint(GLFW_VISIBLE,
                 ((flags & forma::window::VISIBLE) == forma::window::VISIBLE)
                     ? GLFW_TRUE
                     : GLFW_FALSE);
  glfwWindowHint(GLFW_DECORATED, ((flags & forma::window::DECORATED) ==
                                  forma::window::DECORATED)
                                     ? GLFW_TRUE
                                     : GLFW_FALSE);
  glfwWindowHint(GLFW_FOCUSED,
                 ((flags & forma::window::FOCUSED) == forma::window::FOCUSED)
                     ? GLFW_TRUE
                     : GLFW_FALSE);
  glfwWindowHint(GLFW_AUTO_ICONIFY, ((flags & forma::window::AUTO_ICONIFY) ==
                                     forma::window::AUTO_ICONIFY)
                                        ? GLFW_TRUE
                                        : GLFW_FALSE);
  glfwWindowHint(GLFW_FLOATING,
                 ((flags & forma::window::FLOATING) == forma::window::FLOATING)
                     ? GLFW_TRUE
                     : GLFW_FALSE);
  glfwWindowHint(GLFW_MAXIMIZED, ((flags & forma::window::MAXIMIZED) ==
                                  forma::window::MAXIMIZED)
                                     ? GLFW_TRUE
                                     : GLFW_FALSE);
  glfwWindowHint(GLFW_CENTER_CURSOR, ((flags & forma::window::CENTER_CURSOR) ==
                                      forma::window::CENTER_CURSOR)
                                         ? GLFW_TRUE
                                         : GLFW_FALSE);
  glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER,
                 ((flags & forma::window::TRANSPARENT_FRAMEBUFFER) ==
                  forma::window::TRANSPARENT_FRAMEBUFFER)
                     ? GLFW_TRUE
                     : GLFW_FALSE);
  glfwWindowHint(GLFW_FOCUS_ON_SHOW, ((flags & forma::window::FOCUS_ON_SHOW) ==
                                      forma::window::FOCUS_ON_SHOW)
                                         ? GLFW_TRUE
                                         : GLFW_FALSE);
  glfwWindowHint(GLFW_SCALE_TO_MONITOR,
                 ((flags & forma::window::SCALE_TO_MONITOR) ==
                  forma::window::SCALE_TO_MONITOR)
                     ? GLFW_TRUE
                     : GLFW_FALSE);
}
bool construct_window(const std::string& title, const std::size_t& w,
                      const std::size_t& h, const std::uint32_t& flags) {
  forma::logger::initalize_logger(true);
  if (!forma::gl::init_glfw()) {
    return false;
  }
  window_title = title;
  window_hints(flags);
  if ((flags & forma::window::FULLSCREEN) == forma::window::FULLSCREEN) {
    glfw_window =
        glfwCreateWindow(w, h, title.c_str(), glfwGetPrimaryMonitor(), NULL);
  } else {
    glfw_window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
  }
  if (glfw_window == nullptr) {
    LERROR("Failed to construct window using GLFW");
    return false;
  }
  glfwMakeContextCurrent(glfw_window);
  if (!forma::gl::load_gl()) {
    glfwDestroyWindow(glfw_window);
    forma::gl::term_glfw();
    return false;
  }
  return true;
}

bool forma::window::create(std::uint32_t flags) {
  return construct_window("", 100, 100, flags);
}
bool forma::window::create(const std::string& title, std::uint32_t flags) {
  return construct_window(title, 100, 100, flags);
}
bool forma::window::create(const uvec2& dim, std::uint32_t flags) {
  return construct_window("", dim.x, dim.y, flags);
}
bool forma::window::create(const std::string& title, const uvec2& dim,
                           std::uint32_t flags) {
  return construct_window(title, dim.x, dim.y, flags);
}
bool forma::window::create(const uvec2& dim, const std::string& title,
                           std::uint32_t flags) {
  return construct_window(title, dim.x, dim.y, flags);
}
bool forma::window::should_close() {
  return glfwWindowShouldClose(glfw_window);
}
void forma::window::update() {
  glfwSwapBuffers(glfw_window);
  glfwPollEvents();
}
bool forma::window::destroy() {
  if (glfw_window) glfwDestroyWindow(glfw_window);
  return gl::term_glfw();
}

bool forma::window::is_fullscreen() {}
bool forma::window::is_windowed() {}
bool forma::window::is_iconified() {}
bool forma::window::is_maximized() {}
bool forma::window::is_hidden() {}
bool forma::window::is_visible() {}
bool forma::window::is_focused() {}
float forma::window::get_opacity() {}
forma::uvec2 forma::window::get_size() {}
forma::uvec2 forma::window::get_framebuffer_size() {}
forma::vec2 forma::window::get_content_scale() {}

void forma::window::toggle_fullscreen() {}
void forma::window::set_fullscreen(bool setting) {}
void forma::window::toggle_windowed() {}
void forma::window::set_windowed(bool setting) {}
void forma::window::toggle_iconfification() {}
void forma::window::set_iconification(bool setting) {}
void forma::window::toggle_maximization() {}
void forma::window::set_maximization(bool setting) {}
void forma::window::toggle_visibility() {}
void forma::window::set_visibility(bool setting) {}
void forma::window::toggle_focus() {}
void forma::window::set_focus(bool setting) {}
void forma::window::toggle_decoration() {}
void forma::window::set_decoration(bool setting) {}
void forma::window::toggle_resizability() {}
void forma::window::set_resizability(bool setting) {}
void forma::window::toggle_floating() {}
void forma::window::set_floating(bool setting) {}
void forma::window::set_opacity(float val) {}

void forma::window::set_size(const uvec2& size) {}
void forma::window::set_size_limit(const uvec2& min, const uvec2& max) {}
void forma::window::set_aspect_ratio(const uvec2& ratio) {}
void forma::window::set_pos(const uvec2& pos) {}
void forma::window::set_title(const std::string& title) {}
void forma::window::add_icon(const image::Image& img) {}
void forma::window::clear_icons() {}

void forma::window::request_attention() {}
