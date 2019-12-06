add_library(libdfiler io/symlink.cpp)

target_compile_options(libdfiler PRIVATE -Werror)

target_include_directories(libdfiler
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)