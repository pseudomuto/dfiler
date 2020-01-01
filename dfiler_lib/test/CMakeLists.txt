add_executable(libtests
        src/cli/test_command.cpp
        src/cli/test_help_command.cpp
        src/cli/test_symlink_command.cpp
        src/cli/test_options.cpp
        src/test_action_set.cpp
        src/test_image.cpp
        src/test_symlink_action.cpp)

target_link_libraries(libtests PUBLIC dfiler_lib PRIVATE CONAN_PKG::GTest)

include(GoogleTest)
gtest_discover_tests(libtests)
