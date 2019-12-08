cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# extract version details
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION.txt" RAW_VERSION)
string(REGEX MATCH "^[0-9]+\\.[0-9]+\\.[0-9]+" DOTFILES_BASE_VERSION "${RAW_VERSION}")

project(dotfiles
        LANGUAGES CXX
        VERSION "${DOTFILES_BASE_VERSION}")

set(DOTFILES_VERSION_MAJOR "${dotfiles_VERSION_MAJOR}")
set(DOTFILES_VERSION_MINOR "${dotfiles_VERSION_MINOR}")
set(DOTFILES_VERSION_PATCH "${dotfiles_VERSION_PATCH}")

message(STATUS "Dotfiles version: "
        "${DOTFILES_VERSION_MAJOR}.${DOTFILES_VERSION_MINOR}.${DOTFILES_VERSION_PATCH} "
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

################################################################################
# Subdirectories
################################################################################
add_subdirectory(bin)
add_subdirectory(src)
add_subdirectory(test)