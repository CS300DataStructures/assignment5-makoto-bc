project(tests)

add_subdirectory(googletest)

add_executable(tests BST.cpp)
target_link_libraries(tests gtest gtest_main libassignment-5)