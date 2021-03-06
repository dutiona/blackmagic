add_custom_target(tests-compile ALL COMMENT "Build all the unit tests.")

add_custom_target(tests
    DEPENDS tests-compile
    COMMAND ${CMAKE_CTEST_COMMAND} -C ${CMAKE_CONFIGURATION_TYPES} --output-on-failure --schedule-random --verbose
    COMMENT "Build and run all the unit tests.")

macro(add_unit_test Executable)
    set(Sources ${ARGN})
    add_executable(test_${Executable} EXCLUDE_FROM_ALL ${Sources})
    add_test(NAME test_${Executable} COMMAND test_${Executable} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test)
    
    target_link_libraries(test_${Executable} PRIVATE Blackmagic gtest::gtest)
    target_include_directories(test_${Executable} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    
    if(PLATFORM_UNIX AND COMPILER_CLANG)
        target_compile_options(test_${Executable} PRIVATE -Wno-unused-private-field)
    endif()
    
    add_dependencies(tests-compile test_${Executable})
endmacro(add_unit_test)

option(WITH_TESTS "Compile and run tests" ON)

if(WITH_TESTS)

    set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
    find_package(gtest REQUIRED)
    add_subdirectory(blackmagic)

endif(WITH_TESTS)
