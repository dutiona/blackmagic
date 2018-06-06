cmake_minimum_required(VERSION 3.8.2) # required for cxx_std_17

project(Blackmagic VERSION 0.0.1 LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

SET(COMPILER_CLANG OFF)
SET(COMPILER_GCC OFF)
SET(COMPILER_ICC OFF)
SET(COMPILER_MSVC OFF)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    SET(COMPILER_CLANG ON)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET(COMPILER_GCC ON)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    SET(COMPILER_ICC ON)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    SET(COMPILER_MSVC ON)
endif()

SET(PLATFORM_UNIX OFF)
SET(PLATFORM_WIN32 OFF)
SET(PLATFORM_APPLE OFF)

if(WIN32)
    SET(PLATFORM_WIN32 ON)
endif(WIN32)

if(APPLE)
    SET(PLATFORM_APPLE ON)
endif(APPLE)

if(UNIX)
    SET(PLATFORM_UNIX ON)
endif(UNIX)

if(COMPILER_MSVC)
    add_compile_options(/W4 /WX /permissive- /std:c++17)
else(COMPILER_MSVC)
    add_compile_options(-Wall -Wextra -Werror -pedantic)
endif(COMPILER_MSVC)

# option(WITH_CODE_COVERAGE "Add specific compile flag to enable proper code coverage" OFF)
# if(WITH_CODE_COVERAGE)
#
#     SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
#     SET(GCC_COVERAGE_LINK_FLAGS "-lgcov")
#     SET(CLANG_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
#     SET(CLANG_COVERAGE_LINK_FLAGS "--coverage")
#
#     if (COMPILER_CLANG)
#         # using Clang
#         SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CLANG_COVERAGE_COMPILE_FLAGS}")
#         SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${CLANG_COVERAGE_LINK_FLAGS}")
#     elseif (COMPILER_GCC)
#         # using GCC
#         SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
#         SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )
#     elseif (COMPILER_ICC OR COMPILER_MSVC)
#         # using Intel C++ or Visual Studio C++
#         # no coverage
#     endif()
#
# endif(WITH_CODE_COVERAGE)

install(DIRECTORY include DESTINATION include FILES_MATCHING PATTERN "*.hpp")

add_subdirectory(include)

add_subdirectory(doc)

add_subdirectory(example)

add_subdirectory(benchmark)

enable_testing()
add_subdirectory(test)

add_custom_target(check
    DEPENDS examples-compile tests-compile benchmarks-compile
    COMMENT "Build and run all the unit tests, examples and benchmarks.")

add_custom_target(full
    DEPENDS check tests examples benchmarks docs
    COMMENT "Build and run all tests, examples, benchmark in addition to building the documentation.")
