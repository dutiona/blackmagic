add_custom_target(tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMENT "Build and run all the unit tests.")

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

macro(add_unit_test Executable Source)
    add_executable(${Executable} EXCLUDE_FROM_ALL ${Source})
    add_test(NAME ${Executable} COMMAND ${Executable} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test)
    add_dependencies(tests ${Executable})

    target_include_directories(${Executable} PRIVATE ${GTEST_INCLUDE_DIRS})

    if (WIN32)
        target_link_libraries(${Executable} PRIVATE ${GTEST_BOTH_LIBRARIES})
    else (WIN32)
        target_link_libraries(${Executable} PRIVATE ${GTEST_BOTH_LIBRARIES} pthread)
    endif (WIN32)
    
endmacro(add_unit_test)

# regular_type
add_unit_test(regular_type, "regular_type.cpp")


