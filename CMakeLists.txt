cmake_minimum_required(VERSION 3.17)
project(assignment-5)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -Wextra -pedantic)

set(
    SOURCES
    file.cpp
)

add_subdirectory(tests)

add_executable(assignment-5 app.cpp ${SOURCES})
add_library(libassignment-5 STATIC ${SOURCES})