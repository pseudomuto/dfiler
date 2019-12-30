add_executable(libtests src/test_symlink_action.cpp src/test_image.cpp src/test_action_set.cpp src/cli/test_help_command.cpp src/cli/test_options.cpp)
target_link_libraries(libtests PUBLIC dfiler_lib PRIVATE CONAN_PKG::GTest)

include(GoogleTest)
gtest_discover_tests(libtests)
