cmake_minimum_required(VERSION 3.8.2) # required for cxx_std_17

project(Concepts VERSION 0.0.1 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CONCEPTS_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
file(GLOB_RECURSE CONCEPTS_SOURCES  *.hpp)

if(MSVC)
	add_library(Concepts STATIC ${CONCEPTS_INCLUDE_DIR})
	set_target_properties(Concepts PROPERTIES LINKER_LANGUAGE CXX)
	target_compile_features(Concepts PUBLIC cxx_std_17)
	target_include_directories(Concepts PUBLIC ${CONCEPTS_INCLUDE_DIR})
	source_group(TREE ${CONCEPTS_INCLUDE_DIR} FILES ${CONCEPTS_SOURCES})
else(MSVC)
	add_library(Concepts INTERFACE)
	target_compile_features(Concepts INTERFACE cxx_std_17)
	target_include_directories(Concepts INTERFACE ${CONCEPTS_INCLUDE_DIR})
endif(MSVC)


if(MSVC)
    add_compile_options(/W4 /WX /permissive-4 /std:c++17)
else(MSVC)
    add_compile_options(-Wall -Wextra -Werror -pedantic -std=c++1z)
endif(MSVC)

install(FILES     include/concepts.hpp DESTINATION include)
install(DIRECTORY include/concepts     DESTINATION include FILES_MATCHING PATTERN "*.hpp")

add_subdirectory(example)

add_subdirectory(benchmark)

enable_testing()
add_subdirectory(test)

# Setup the `check` convenience target, which is equivalent to examples + tests.
add_custom_target(check
    DEPENDS examples tests benchmarks
    COMMENT "Build and run all the unit tests and examples.")
