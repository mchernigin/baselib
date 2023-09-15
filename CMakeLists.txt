cmake_minimum_required(VERSION 3.15)

project(baselib
  LANGUAGES CXX
  VERSION 0.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)

##########
# Logger #
##########

add_library(logger)

target_sources(logger PRIVATE
  src/logger/loggermanager.cpp
  src/logger/logger.cpp
  src/logger/consolelogger.cpp
  src/logger/filelogger.cpp
  src/logger/sysloglogger.cpp
)

target_include_directories(
    logger PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/logger/>"
                 "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

find_package(Qt5 COMPONENTS Core REQUIRED)
target_link_libraries(logger Qt5::Core)

install(
    TARGETS logger
    EXPORT logger-config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/include/logger/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/logger/")

install(
    EXPORT logger-config
    NAMESPACE "${PROJECT_NAME}::"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

##################
# Project config #
##################

file(GLOB COMMON_INCLUDES "${PROJECT_SOURCE_DIR}/include/*.h")

install(FILES ${COMMON_INCLUDES}
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/")

configure_file(
    ${PROJECT_NAME}-config.cmake.in
    ${PROJECT_NAME}-config.cmake
    @ONLY)

install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

