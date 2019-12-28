add_executable(tests test_test.cpp)
target_link_libraries(tests INTERFACE dfiler PRIVATE CONAN_PKG::GTest)

include(GoogleTest)
gtest_discover_tests(tests)
