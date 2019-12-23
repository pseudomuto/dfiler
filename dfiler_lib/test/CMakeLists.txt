add_executable(libtests io/test_symlink.cpp)
target_link_libraries(libtests PUBLIC dfiler_lib PRIVATE CONAN_PKG::GTest)

include(GoogleTest)
gtest_discover_tests(libtests)
