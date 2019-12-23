add_executable(dfiler src/dfiler.cpp)
target_link_libraries(dfiler PUBLIC dfiler_lib)

add_subdirectory("test")
