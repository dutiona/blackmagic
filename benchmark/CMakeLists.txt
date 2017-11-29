add_custom_target(benchmarks
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMENT "Build and run all the benchmarks.")

find_package(benchmark REQUIRED)

macro(add_unit_test Executable Source)
    add_executable(${Executable} EXCLUDE_FROM_ALL ${Source})
    target_compile_options(${Executable} PRIVATE -O3)
    target_link_libraries(${Executable} PRIVATE benchmark::benchmark)
    add_test(NAME ${Executable} COMMAND ${Executable} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/benchmark)
    add_dependencies(benchmarks ${Executable})
endmacro(add_unit_test)

# regular_type
add_unit_test(regular_type, "regular_type.cpp")


