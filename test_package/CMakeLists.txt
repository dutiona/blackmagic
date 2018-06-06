project(PackageTest CXX)
cmake_minimum_required(VERSION 3.8.2)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(test test.cpp)
target_link_libraries(test PRIVATE CONAN_PKG::blackmagic)
target_compile_features(test INTERFACE cxx_std_17)

enable_testing()
add_test(NAME test
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        COMMAND test)
