cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# extract version details
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION.txt" RAW_VERSION)
string(REGEX MATCH "^[0-9]+\\.[0-9]+\\.[0-9]+" DFILER_BASE_VERSION "${RAW_VERSION}")

project(dfiler
        LANGUAGES CXX
        VERSION "${DFILER_BASE_VERSION}")

set(DFILER_VERSION_MAJOR "${dfiler_VERSION_MAJOR}")
set(DFILER_VERSION_MINOR "${dfiler_VERSION_MINOR}")
set(DFILER_VERSION_PATCH "${dfiler_VERSION_PATCH}")

message(STATUS "dfiler version: "
        "${DFILER_VERSION_MAJOR}.${DFILER_VERSION_MINOR}.${DFILER_VERSION_PATCH} "
        "(full: '${RAW_VERSION}')")

include(ExternalProject)
include(GNUInstallDirs)

################################################################################
# Compiler details
################################################################################
include(SetupCxxFlags)

option(CODE_COVERAGE "Enable coverage reporting" OFF)
if (CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    include(CodeCov)
endif ()

option(IWYU "Run include-what-you-use with the compiler" OFF)
if (IWYU)
    find_program(IWYU_COMMAND NAMES include-what-you-use iwyu)
    if(NOT IWYU_COMMAND)
        message(FATAL_ERROR "CMAKE_IWYU is ON but include-what-you-use is not found!")
    endif()
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "${IWYU_COMMAND};-Xiwyu;--mapping_file=${CMAKE_SOURCE_DIR}/iwyu.imp")
endif ()

################################################################################
# Dependencies
################################################################################
enable_testing()
include(Conan)

################################################################################
# Subdirectories
################################################################################
add_subdirectory(dfiler)
add_subdirectory(dfiler_lib)
