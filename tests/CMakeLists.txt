cmake_minimum_required(VERSION 3.5)

set(This JsonTests)

project(${This} C CXX)

add_executable(${This}
    test01.cpp
)

target_link_libraries(${This}
    gtest_main
    jsonParser
)

include_directories()

add_custom_command(
        TARGET ${This} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/test.json
                ${CMAKE_CURRENT_BINARY_DIR}/test.json)

add_test(
     NAME ${This}
     COMMAND ${This}
)
