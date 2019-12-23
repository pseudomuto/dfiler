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
    include(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS()
endif ()

################################################################################
# Dependencies
################################################################################
enable_testing()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

################################################################################
# Subdirectories
################################################################################
add_subdirectory(dfiler)
add_subdirectory(dfiler_lib)
