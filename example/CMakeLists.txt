cmake_minimum_required(VERSION 3.15)
project(qbase-example LANGUAGES CXX)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(qbase COMPONENTS logger REQUIRED)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE qbase::logger Qt5::Core)
