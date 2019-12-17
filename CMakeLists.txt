# ##############################################################################
# PROJECT
# ##############################################################################
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(
  Forma
  VERSION 0.0.6
  LANGUAGES C CXX)

option(STATIC_ANALYSIS "Enable static analysis" FALSE)
option(BUILD_SHARED "Compile shared library" FALSE)
option(DOCS "Compile documentation" FALSE)
option(EXAMPLES "Compiles examples" TRUE)
option(USE_GLES, "Use EGL" FALSE)

# ##############################################################################
# SOURCE
# ##############################################################################
set(SOURCE src/log.cpp)
if(USE_GLES)
  list(APPEND SOURCES src/glad_egl.c)
else()
  list(APPEND SOURCES src/glad.c)
endif()
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
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external)

add_library(${PROJECT_NAME}_static STATIC ${SOURCE})
add_library(${PROJECT_NAME}::static ALIAS ${PROJECT_NAME}_static)

target_include_directories(${PROJECT_NAME}_static
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(
  ${PROJECT_NAME}_static PRIVATE -Wall -Wextra
  $<$<CONFIG:Debug>:-O0>$<$<CONFIG:Release>:-O3>)
target_compile_definitions(${PROJECT_NAME}_static PRIVATE
  $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:RELEASE>)
set_target_properties(
  ${PROJECT_NAME}_static PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED TRUE
  CXX_EXTENSIONS TRUE)

target_link_libraries(${PROJECT_NAME}_static PUBLIC glfw)
target_link_libraries(${PROJECT_NAME}_static PUBLIC spdlog::spdlog)
target_link_libraries(${PROJECT_NAME}_static PUBLIC glm::glm_static)
target_link_libraries(${PROJECT_NAME}_static PUBLIC ${CMAKE_DL_LIBS})

install(TARGETS ${PROJECT_NAME}_static)

if(BUILD_SHARED)
  add_library(${PROJECT_NAME}_shared SHARED ${SOURCE})
  add_library(${PROJECT_NAME}::shared ALIAS ${PROJECT_NAME}_shared)

  target_include_directories(${PROJECT_NAME}_shared
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
  target_compile_options(
    ${PROJECT_NAME}_shared
    PRIVATE -Wall -Wextra $<$<CONFIG:Debug>:-O0>$<$<CONFIG:Release>:-O3>)
  target_compile_definitions(
    ${PROJECT_NAME}_shared PRIVATE
    $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:RELEASE>)
  set_target_properties(
    ${PROJECT_NAME}_shared PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED
    TRUE CXX_EXTENSIONS TRUE)

  target_link_libraries(${PROJECT_NAME}_shared PUBLIC glfw)
  target_link_libraries(${PROJECT_NAME}_shared PUBLIC spdlog::spdlog)
  target_link_libraries(${PROJECT_NAME}_shared PUBLIC glm::glm_shared)
  target_link_libraries(${PROJECT_NAME}_shared PUBLIC ${CMAKE_DL_LIBS})

  install(TARGETS ${PROJECT_NAME}_shared)

  add_library(${PROJECT_NAME} ALIAS ${PROJECT_NAME}_shared)
else()
  add_library(${PROJECT_NAME} ALIAS ${PROJECT_NAME}_static)
endif()

if(EXAMPLES)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/samples)
endif()
if(DOCS)
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
