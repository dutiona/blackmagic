cmake_minimum_required(VERSION 3.6)

project(Cpp14Concepts VERSION 0.0.1 LANGUAGES CXX)

add_library(Cpp14Concepts INTERFACE)
target_compile_features(Cpp14Concepts INTERFACE cxx_std_14)
target_include_directories(Cpp14Concepts
    INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")

if(MSVC)
    add_compile_options(/W4 /WX /permissive- /std:c++14)
else(MSVC)
    add_compile_options(-Wall -Wextra -Werror -pedantic -std=c++14)
endif(MSVC)

install(TARGETS   Cpp14Concepts INCLUDES    DESTINATION include)
install(FILES     include/cpp14concepts.hpp DESTINATION include)
install(DIRECTORY include/cpp14concepts     DESTINATION include FILES_MATCHING PATTERN "*.hpp")

add_subdirectory(example)

add_subdirectory(benchmark)

enable_testing()
add_subdirectory(test)

# Setup the `check` convenience target, which is equivalent to examples + tests.
add_custom_target(check
    DEPENDS examples tests benchmarks
    COMMENT "Build and run all the unit tests and examples.")
