add_custom_target(benchmarks
    COMMENT "Build and run all the benchmarks.")

macro(add_benchmark Executable Source)
    add_executable(benchmark_${Executable}.exe EXCLUDE_FROM_ALL ${Source})

    target_link_libraries(benchmark_${Executable}.exe PRIVATE Concepts)
    target_link_libraries(benchmark_${Executable}.exe PRIVATE benchmark::benchmark)
    target_compile_options(benchmark_${Executable}.exe PRIVATE -O3)
    target_include_directories(benchmark_${Executable}.exe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    add_custom_target(benchmark_${Executable}
        COMMAND benchmark_${Executable}.exe
        DEPENDS benchmark_${Executable}.exe
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/benchmark
        USES_TERMINAL)
        
    add_dependencies(benchmarks benchmark_${Executable})
endmacro(add_benchmark)

option(WITH_BENCHMARK "Enable benchmark (requires google benchmark installed" OFF)

if(WITH_BENCHMARK)

    find_package(benchmark REQUIRED)
    add_benchmark(empty "empty.cpp")

endif(WITH_BENCHMARK)

