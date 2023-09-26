find_package(Qt5 COMPONENTS Core REQUIRED)

add_qbase_library(logger SHARED
  loggermanager.cpp
  loggermessage.cpp
  logger.cpp
  consolelogger.cpp
  filelogger.cpp
  sysloglogger.cpp
)

target_link_libraries(logger Qt5::Core)

