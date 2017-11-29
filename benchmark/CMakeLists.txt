add_custom_target(benchmarks
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMENT "Build and run all the benchmarks.")

find_package(benchmark REQUIRED)

macro(add_benchmark Executable Source)
    add_executable(benchmark_${Executable}.exe EXCLUDE_FROM_ALL ${Source})
    target_compile_options(benchmark_${Executable}.exe PRIVATE -O3)
    target_link_libraries(benchmark_${Executable}.exe PRIVATE benchmark::benchmark)
    add_custom_target(benchmark_${Executable} COMMAND benchmark_${Executable}.exe DEPENDS benchmark_${Executable}.exe WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/benchmark USES_TERMINAL)
    add_dependencies(benchmarks benchmark_${Executable})
endmacro(add_benchmark)

# regular_type
add_benchmark(regular_type "regular_type.cpp")


