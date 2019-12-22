add_executable(tests io/test_symlink.cpp)
target_link_libraries(tests PUBLIC libdfiler PRIVATE CONAN_PKG::GTest)

include(GoogleTest)
gtest_discover_tests(tests)
