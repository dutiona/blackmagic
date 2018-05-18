add_custom_target(tests-compile ALL COMMENT "Build all the unit tests.")

add_custom_target(tests EXCLUDE_FROM_ALL
    DEPENDS tests-compile
    COMMAND ${CMAKE_CTEST_COMMAND} -C ${CMAKE_CONFIGURATION_TYPES} --output-on-failure --schedule-random --verbose
    COMMENT "Build and run all the unit tests.")

macro(add_unit_test Executable Source)
    add_executable(test_${Executable} EXCLUDE_FROM_ALL ${Source})
    add_test(NAME test_${Executable} COMMAND test_${Executable} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test)
    
    target_link_libraries(test_${Executable} PRIVATE Blackmagic)
    target_include_directories(test_${Executable} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_include_directories(test_${Executable} PRIVATE ${GTEST_INCLUDE_DIRS})
    
    if(PLATFORM_UNIX AND COMPILER_CLANG)
        target_compile_options(test_${Executable} PRIVATE -Wno-unused-private-field)
    endif()
    
    if (PLATFORM_WIN32)
        target_link_libraries(test_${Executable} PRIVATE ${GTEST_BOTH_LIBRARIES})
    else (PLATFORM_WIN32)
        target_link_libraries(test_${Executable} PRIVATE ${GTEST_BOTH_LIBRARIES} pthread)
    endif (PLATFORM_WIN32)
    
    add_dependencies(tests-compile test_${Executable})
endmacro(add_unit_test)

option(WITH_TESTS "Compile and run tests" ON)

if(WITH_TESTS)

    find_package(Threads REQUIRED)
    find_package(GTest REQUIRED)

    add_subdirectory(blackmagic)

endif(WITH_TESTS)
