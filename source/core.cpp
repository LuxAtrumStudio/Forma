#include "core.hpp"

#include <estl/logger.hpp>

#include "gl.hpp"

void GlfwErrorHandle(int error_num, const char* error_msg){
  estl::logger::Logger::Get()->GetLogger()->_LogError(error_msg, "GLFW", "", error_num);
}

bool forma::InitForma() {
  estl::logger::Version("Forma Version: %i.%i", FORMA_VERSION_MAJOR,
                        FORMA_VERSION_MINOR);
  estl::logger::Version("OpenGL Version: %i.%i", GL_VERSION_MAJOR,
                        GL_VERSION_MINOR);
  InitGlfw();
  InitGlad();
  return true;
}

bool forma::InitGlad() {
  if(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false){
    estl::logger::Fatal("Failed to initialize GLAD");
    return false;
  }else{
    return true;
  }
}

bool forma::InitGlfw() {
  glfwSetErrorCallback(GlfwErrorHandle);
  if (glfwInit() == false) {
    estl::logger::Fatal("Failed to initialize GLFW");
    return false;
  } else {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    estl::logger::Version("GFLW Version: %i.%i", GLFW_VERSION_MAJOR,
                          GLFW_VERSION_MINOR);
    return true;
  }
}
