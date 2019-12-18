#include "forma/window.hpp"

#include <cstdlib>
#include <string>
#include <vector>

#include "forma/gl.hpp"
#include "forma/image.hpp"
#include "forma/log.hpp"
#include "forma/math.hpp"

static GLFWwindow* glfw_window;
static int glfw_xpos, glfw_ypos, glfw_width, glfw_height;
static std::string glfw_title;
static std::vector<forma::image::Image> glfw_icons;

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
  glfw_title = title;
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
  glfw_width = w;
  glfw_height = h;
  glfwGetWindowPos(glfw_window, &glfw_xpos, &glfw_ypos);

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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glfwPollEvents();
}
bool forma::window::destroy() {
  if (glfw_window) glfwDestroyWindow(glfw_window);
  return gl::term_glfw();
}

bool forma::window::is_fullscreen() {
  return glfwGetWindowMonitor(glfw_window) != nullptr;
}
bool forma::window::is_windowed() {
  return glfwGetWindowMonitor(glfw_window) == nullptr;
}
bool forma::window::is_iconified() {
  return glfwGetWindowAttrib(glfw_window, GLFW_ICONIFIED) == GLFW_TRUE;
}
bool forma::window::is_maximized() {
  return glfwGetWindowAttrib(glfw_window, GLFW_MAXIMIZED) == GLFW_TRUE;
}
bool forma::window::is_hidden() {
  return glfwGetWindowAttrib(glfw_window, GLFW_VISIBLE) == GLFW_FALSE;
}
bool forma::window::is_visible() {
  return glfwGetWindowAttrib(glfw_window, GLFW_VISIBLE) == GLFW_TRUE;
}
bool forma::window::is_focused() {
  return glfwGetWindowAttrib(glfw_window, GLFW_FOCUSED) == GLFW_TRUE;
}
float forma::window::get_opacity() { return glfwGetWindowOpacity(glfw_window); }
forma::uvec2 forma::window::get_size() {
  glfwGetWindowSize(glfw_window, &glfw_width, &glfw_height);
  return {glfw_width, glfw_height};
}
forma::uvec2 forma::window::get_pos() {
  glfwGetWindowPos(glfw_window, &glfw_xpos, &glfw_ypos);
  return {glfw_xpos, glfw_ypos};
}
forma::uvec2 forma::window::get_framebuffer_size() {
  int x, y;
  glfwGetFramebufferSize(glfw_window, &x, &y);
  return {x, y};
}
forma::vec2 forma::window::get_content_scale() {
  vec2 scale;
  glfwGetWindowContentScale(glfw_window, &scale.x, &scale.y);
  return scale;
}

void forma::window::toggle_fullscreen() {
  if (is_fullscreen()) {
    glfwSetWindowMonitor(glfw_window, NULL, glfw_xpos, glfw_ypos, glfw_width,
                         glfw_height, 0);
  } else {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowMonitor(glfw_window, glfwGetPrimaryMonitor(), 0, 0,
                         mode->width, mode->height, mode->refreshRate);
  }
}
void forma::window::set_fullscreen(bool setting) {
  if (is_fullscreen() == setting) {
    return;
  } else if (setting) {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowMonitor(glfw_window, glfwGetPrimaryMonitor(), 0, 0,
                         mode->width, mode->height, mode->refreshRate);
  } else {
    glfwSetWindowMonitor(glfw_window, NULL, glfw_xpos, glfw_ypos, glfw_width,
                         glfw_height, 0);
  }
}
void forma::window::toggle_windowed() {
  if (is_fullscreen()) {
    glfwSetWindowMonitor(glfw_window, NULL, glfw_xpos, glfw_ypos, glfw_width,
                         glfw_height, 0);
  } else {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowMonitor(glfw_window, glfwGetPrimaryMonitor(), 0, 0,
                         mode->width, mode->height, mode->refreshRate);
  }
}
void forma::window::set_windowed(bool setting) {
  if (is_windowed() == setting) {
    return;
  } else if (setting) {
    glfwSetWindowMonitor(glfw_window, NULL, glfw_xpos, glfw_ypos, glfw_width,
                         glfw_height, 0);
  } else {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowMonitor(glfw_window, glfwGetPrimaryMonitor(), 0, 0,
                         mode->width, mode->height, mode->refreshRate);
  }
}
void forma::window::toggle_iconfification() {
  if (is_iconified()) {
    glfwRestoreWindow(glfw_window);
  } else {
    glfwIconifyWindow(glfw_window);
  }
}
void forma::window::set_iconification(bool setting) {
  if (is_iconified() == setting) {
    return;
  } else if (setting) {
    glfwIconifyWindow(glfw_window);
  } else {
    glfwRestoreWindow(glfw_window);
  }
}
void forma::window::toggle_maximization() {
  if (is_maximized()) {
    glfwRestoreWindow(glfw_window);
  } else {
    glfwMaximizeWindow(glfw_window);
  }
}
void forma::window::set_maximization(bool setting) {
  if (is_maximized() == setting) {
    return;
  } else if (setting) {
    glfwMaximizeWindow(glfw_window);
  } else {
    glfwRestoreWindow(glfw_window);
  }
}
void forma::window::toggle_visibility() {
  if (is_visible()) {
    glfwHideWindow(glfw_window);
  } else {
    glfwShowWindow(glfw_window);
  }
}
void forma::window::set_visibility(bool setting) {
  if (is_visible() == setting) {
    return;
  } else if (setting) {
    glfwShowWindow(glfw_window);
  } else {
    glfwHideWindow(glfw_window);
  }
}
void forma::window::get_focus() { glfwFocusWindow(glfw_window); }
void forma::window::toggle_decoration() {
  glfwSetWindowAttrib(glfw_window, GLFW_DECORATED,
                      !glfwGetWindowAttrib(glfw_window, GLFW_DECORATED));
}
void forma::window::set_decoration(bool setting) {
  glfwSetWindowAttrib(glfw_window, GLFW_DECORATED, setting);
}
void forma::window::toggle_resizability() {
  glfwSetWindowAttrib(glfw_window, GLFW_RESIZABLE,
                      !glfwGetWindowAttrib(glfw_window, GLFW_RESIZABLE));
}
void forma::window::set_resizability(bool setting) {
  glfwSetWindowAttrib(glfw_window, GLFW_RESIZABLE, setting);
}
void forma::window::toggle_floating() {
  glfwSetWindowAttrib(glfw_window, GLFW_FLOATING,
                      !glfwGetWindowAttrib(glfw_window, GLFW_FLOATING));
}
void forma::window::set_floating(bool setting) {
  glfwSetWindowAttrib(glfw_window, GLFW_FLOATING, setting);
}
void forma::window::set_opacity(float val) {
  glfwSetWindowOpacity(glfw_window, val);
}

void forma::window::set_size(const uvec2& size) {
  glfw_width = size.x;
  glfw_height = size.y;
  glfwSetWindowSize(glfw_window, size.x, size.y);
}
void forma::window::set_size_limit(const uvec2& min, const uvec2& max) {
  glfwSetWindowSizeLimits(glfw_window, min.x, min.y, max.x, max.y);
}
void forma::window::set_aspect_ratio(const uvec2& ratio) {
  glfwSetWindowAspectRatio(glfw_window, ratio.x, ratio.y);
}
void forma::window::set_pos(const uvec2& pos) {
  glfw_xpos = pos.x;
  glfw_ypos = pos.y;
  glfwSetWindowPos(glfw_window, pos.x, pos.y);
}
void forma::window::set_title(const std::string& title) {
  glfw_title = title;
  glfwSetWindowTitle(glfw_window, title.c_str());
}
void forma::window::add_icon(const image::Image& img) {
  glfw_icons.push_back(img);
  std::vector<GLFWimage> icon_array(glfw_icons.begin(), glfw_icons.end());
  glfwSetWindowIcon(glfw_window, icon_array.size(), icon_array.data());
}
void forma::window::clear_icons() {
  glfw_icons.clear();
  glfwSetWindowIcon(glfw_window, 0, NULL);
}

void forma::window::request_attention() {
  glfwRequestWindowAttention(glfw_window);
}
