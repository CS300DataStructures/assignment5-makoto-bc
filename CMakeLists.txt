cmake_minimum_required(VERSION 3.17)
project(assignment-5)

set(CMAKE_CXX_STANDARD 14)

set(
    SOURCES
)

add_subdirectory(tests)

add_executable(assignment-5 app.cpp ${SOURCES})
add_library(libassignment-5 STATIC ${SOURCES})
set_target_properties(libassignment-5 PROPERTIES LINKER_LANGUAGE CXX)
add_compile_options(-Wall -Wextra -pedantic)