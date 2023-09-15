cmake_minimum_required(VERSION 3.15)

project(baselib
  LANGUAGES CXX
  VERSION 0.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)

add_subdirectory(src)

file(GLOB COMMON_INCLUDES "${PROJECT_SOURCE_DIR}/include/*.h")
install(
  FILES ${COMMON_INCLUDES}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/")

configure_file(
  ${PROJECT_NAME}-config.cmake.in
  ${PROJECT_NAME}-config.cmake
  @ONLY)

install(
  FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

