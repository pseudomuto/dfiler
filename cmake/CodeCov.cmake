# Prerequisites
find_program(GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/scripts/test)

set(CMAKE_CXX_FLAGS_CODECOV "-O0 -g --coverage" CACHE INTERNAL "")
mark_as_advanced(CMAKE_CXX_FLAGS_CODECOV)

# Ensure we're using a debug build
string(TOLOWER ${CMAKE_BUILD_TYPE} current_build_type)
if (NOT current_build_type STREQUAL "debug")
    message(WARNING "Code coverage results with an optimised (non-Debug) build may be misleading")
endif ()

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    link_libraries(gcov)
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_CODECOV}")
message(STATUS "Appending code coverage compiler flags: ${CMAKE_CXX_FLAGS_CODECOV}")

add_custom_target(codecov
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMENT "Generating code cov report at ${PROJECT_BINARY_DIR}/codecov.xml"
        COMMAND ${GCOVR_PATH} -r .. --object-directory "${PROJECT_BINARY_DIR}"
        COMMAND ${GCOVR_PATH} --xml -r .. --object-directory "${PROJECT_BINARY_DIR}" -o codecov.xml)