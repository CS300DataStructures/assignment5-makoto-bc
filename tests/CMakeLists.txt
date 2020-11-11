project(tests)

add_subdirectory(googletest)

add_executable(tests BST.cpp file.cpp)
target_link_libraries(tests gtest gtest_main libassignment-5)