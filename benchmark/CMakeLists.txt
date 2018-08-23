add_custom_target(benchmarks-compile ALL COMMENT "Build all the benchmarks.")

add_custom_target(benchmarks
        DEPENDS benchmarks-compile
        COMMENT "Build and run all the benchmarks.")

macro(add_benchmark Executable Source)
    add_executable(benchmark_${Executable}.exe EXCLUDE_FROM_ALL ${Source})

    target_link_libraries(benchmark_${Executable}.exe PRIVATE Blackmagic benchmark::benchmark Threads::Threads)
	if(MSVC)
		#only with 15.6 preview as of now
		# target_compile_options(benchmark_${Executable}.exe PRIVATE /experimental:external /external:anglebracket /external:wd4141) # 'inline': used more than once
	else(MSVC)
		target_compile_options(benchmark_${Executable}.exe PRIVATE -O3)
	endif(MSVC)
    target_include_directories(benchmark_${Executable}.exe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    add_dependencies(benchmarks-compile benchmark_${Executable}.exe)

    add_custom_target(benchmark_${Executable}
        COMMAND benchmark_${Executable}.exe
        DEPENDS benchmark_${Executable}.exe
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/benchmark
        USES_TERMINAL)
        
    add_dependencies(benchmarks benchmark_${Executable})
endmacro(add_benchmark)

option(WITH_BENCHMARKS "Enable benchmark (requires google benchmark installed)" OFF)

if(WITH_BENCHMARKS)

    set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
    find_package(benchmark REQUIRED)
    find_package(Threads REQUIRED)
    add_subdirectory(blackmagic)

endif(WITH_BENCHMARKS)

