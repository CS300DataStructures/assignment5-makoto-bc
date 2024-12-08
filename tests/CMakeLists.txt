project(tests)

add_subdirectory(googletest)

add_compile_options(-Wall -Wextra -pedantic)

add_executable(tests BST.cpp file.cpp)
target_link_libraries(tests gtest gtest_main libassignment-5)

add_executable(fuzz fuzz.cpp)
target_link_libraries(fuzz libassignment-5)
target_compile_options(fuzz PRIVATE -fsanitize=fuzzer,address,signed-integer-overflow)
target_link_options(fuzz PRIVATE -fsanitize=fuzzer,address,signed-integer-overflow)