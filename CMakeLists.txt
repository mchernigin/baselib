cmake_minimum_required(VERSION 3.0)

project(baselib VERSION 0.0.1)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    src/logger/consolelogger.cpp
    src/logger/filelogger.cpp
    src/logger/logger.cpp
    src/logger/loggermanager.cpp
    src/logger/sysloglogger.cpp)

add_library(baselib SHARED ${SOURCES})
set_target_properties(baselib PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1)

target_include_directories(baselib PRIVATE include)

find_package(
  Qt5
  COMPONENTS Core
  REQUIRED)
target_include_directories(baselib PUBLIC ${Qt5Gui_INCLUDE_DIRS})
target_link_libraries(baselib Qt5::Core)

include(GNUInstallDirs)

install(
  DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME}/"
  FILES_MATCHING
  PATTERN "*.h")

install(
  TARGETS baselib
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")

