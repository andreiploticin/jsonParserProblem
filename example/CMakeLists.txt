cmake_minimum_required(VERSION 3.5)

project(example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(example
    example.cpp
    )

target_link_libraries (example LINK_PUBLIC jsonParser)
