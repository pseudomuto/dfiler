add_library(dfiler_lib
        src/action_set.cpp
        src/cli/command.cpp
        src/cli/help_command.cpp
        src/cli/options.cpp
        src/cli/symlink_command.cpp
        src/image.cpp
        src/symlink_action.cpp)

target_include_directories(dfiler_lib
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(dfiler_lib PRIVATE CONAN_PKG::cxxopts)

add_subdirectory("test")
