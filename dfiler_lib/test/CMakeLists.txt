add_executable(libtests src/test_symlink_action.cpp)
target_link_libraries(libtests PUBLIC dfiler_lib PRIVATE CONAN_PKG::GTest)

include(GoogleTest)
gtest_discover_tests(libtests)
