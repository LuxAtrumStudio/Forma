// #include <GLFW/glfw3.h>
#include <forma/forma.hpp>

int main(void)
{
    if(!forma::initalize()) return -1;

    forma::graphics::Window window(640, 480, "Hello World");
    if(!window.valid()) {
      forma::terminate();
      return -1;
    }
    // /* Loop until the user closes the window */
    // while (!glfwWindowShouldClose(window))
    // {
    //     /* Render here */
    //     // glClear(GL_COLOR_BUFFER_BIT);
    //
    //     /* Swap front and back buffers */
    //     glfwSwapBuffers(window);
    //
    //     /* Poll for and process events */
    //     glfwPollEvents();
    // }

    window.destroy();
    forma::terminate();
    return 0;
}
