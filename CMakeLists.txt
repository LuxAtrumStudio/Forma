# ##############################################################################
# PROJECT
# ##############################################################################
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(Forma VERSION 0.0.3 LANGUAGES C CXX)

option(STATIC_ANALYSIS "Enable static analysis" FALSE)
option(EXAMPLES "Compiles examples" TRUE)
set(GL_VERSION "4.4" STRING "OpenGL version to use")
list(GET GL_VERSION 0 GL_VERSION)
string(REPLACE "." ";" GL_VERSION_LIST ${GL_VERSION})
list(GET GL_VERSION_LIST 0 GL_VERSION_MAJOR)
list(GET GL_VERSION_LIST 1 GL_VERSION_MINOR)
message(STATUS "Using OpenGL: ${GL_VERSION_MAJOR}.${GL_VERSION_MINOR}")

# ##############################################################################
# SOURCE
# ##############################################################################
set(SOURCE
  src/forma.cpp
  src/log.cpp
  src/graphics/graphics.cpp
  src/gl/gl.cpp
  src/gl/glad.c
  src/gl/glfw.cpp
  )
configure_file("${PROJECT_SOURCE_DIR}/include/forma/version.hpp.in"
  "${PROJECT_SOURCE_DIR}/include/forma/version.hpp")
set(FORMA_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(FORMA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# ##############################################################################
# BUILD TYPE
# ##############################################################################
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE
    "Debug"
    CACHE STRING "Choose the type of build" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
  if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    execute_process(
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
      ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
      ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
  endif()
endif()

# ##############################################################################
# STATIC ANALYSIS
# ##############################################################################
if(STATIC_ANALYSIS OR CMAKE_BUILD_TYPE STREQUAL "Release")
  find_program(CLANG_TIDY "clang-tidy")
  if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
  endif()
  find_program(CPPCHECK "cppcheck")
  if(CPPCHECK)
    set(CMAKE_CXX_CPPCHECK ${CPPCHECK})
    list(APPEND CMAKE_CXX_CPPCHECK "--force")
  endif()
  find_program(CPPLINT "cpplint")
  if(CPPLINT)
    set(CMAKE_CXX_CPPLINT ${CPPLINT})
  endif()
endif()

# ##############################################################################
# TARGETS
# ##############################################################################
find_package(Git REQUIRED)
add_library(${PROJECT_NAME} STATIC ${SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra $<$<CONFIG:Debug>:-O0>$<$<CONFIG:Release>:-O3>)
target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:RELEASE>)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED TRUE CXX_EXTENSIONS TRUE)
install(TARGETS ${PROJECT_NAME})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})

if(EXAMPLES)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
endif()

# ##############################################################################
# PACKAGING
# ##############################################################################
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CPACK_GENERATOR "STGZ;TGZ;ZIP")
  set(CPACK_PACKAGE_VENDOR "LuxAter")
  set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
  set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
  set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
  set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
  set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md")
  set(CPACK_MONOLITHIC_INSTALL TRUE)
  include(CPack)
endif()

