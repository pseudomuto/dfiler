add_library(dfiler_lib src/symlink_action.cpp src/image.cpp src/action_set.cpp)

target_include_directories(dfiler_lib
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory("test")
