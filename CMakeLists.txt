cmake_minimum_required(VERSION 3.0)

project(baselib)

set(SOURCES
    main.cpp)

add_subdirectory(logger)

add_library(baselib STATIC ${SOURCES})
