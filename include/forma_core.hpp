/* Copyright (C)
 * 2017 - Arden Rasmussen
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef FORMA_FORMA_CORE_HPP
#define FORMA_FORMA_CORE_HPP

#define FORMA_VERSION_MAJOR 0
#define FORMA_VERSION_MINOR 0

/**
 * @brief Main namespace for all Forma objects.
 *
 * This namespace is the base of the namespace library, all objects are defined
 * within the namespace, and posibly in sub namespaces based on the module of
 * Forma that the object or function is intended for.
 */
namespace forma {
  /**
   * @brief Initializes Forma
   *
   * Initialized Forma, aswell as GLFW and GLAD for the user. This must allways
   * be called before any other call to a Forma method.
   */
  void InitForma();
  /**
   * @brief Initalizes GLAD
   *
   * Initializes GLAD, or throws an error and logs the error message.
   */
  void InitGlad();
  /**
   * @brief Initalizes GLFW
   *
   * Initializes GLFW, or throws an error and logs the error message.
   */
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
