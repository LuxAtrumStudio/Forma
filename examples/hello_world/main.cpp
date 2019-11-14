// #include <GLFW/glfw3.h>
#include <forma/forma.hpp>

int main(void) {
  if (!forma::graphics::window::create_window(640, 480, "Hello world")) {
    forma::terminate();
    return -1;
  }
  while (!forma::graphics::window::should_close()) {
    forma::graphics::window::swap();
    //     /* Render here */
    //     // glClear(GL_COLOR_BUFFER_BIT);
    //
    //     /* Swap front and back buffers */
    //     glfwSwapBuffers(window);
    //
    //     /* Poll for and process events */
    //     glfwPollEvents();
  }

  forma::terminate();
  return 0;
}
