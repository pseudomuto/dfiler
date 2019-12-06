include(GoogleTest)

add_executable(tests io/test_symlink.cpp)
target_link_libraries(tests PUBLIC libdfiler)
add_gtest(tests)