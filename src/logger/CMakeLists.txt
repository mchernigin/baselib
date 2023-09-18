find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(logger SHARED
  loggermanager.cpp
  loggermessage.cpp
  logger.cpp
  consolelogger.cpp
  filelogger.cpp
  sysloglogger.cpp
)

target_link_libraries(logger Qt5::Core)

target_include_directories(
  logger PUBLIC "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/logger/>"
                "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
install(
  TARGETS logger
  EXPORT logger-config
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(
  DIRECTORY "${CMAKE_SOURCE_DIR}/include/logger/"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/logger/")

install(
  EXPORT logger-config
  NAMESPACE "${PROJECT_NAME}::"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

