cmake_minimum_required(VERSION 3.5)

project(jsonParser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(jsonParser
    src/jsonbasevalue.cpp
    src/jsonbasevalue.h
    src/jsonparser.cpp
    src/jsonparser.h
    )


enable_testing()
add_subdirectory(googletest)
add_subdirectory(tests)
add_subdirectory(example)
