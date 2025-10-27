cmake_minimum_required(VERSION 3.20)

project(GostTranslate CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library

file(GLOB CXX_SOURCES "src/*.cpp")

list(APPEND SOURCES ${CXX_SOURCES})

add_library(GostTranslate ${SOURCES})

target_include_directories(GostTranslate PRIVATE "include")

# Tests

add_executable(unit01 "tests/unittest_01.cpp")
target_include_directories(unit01 PRIVATE "include")
target_link_libraries(unit01 GostTranslate)