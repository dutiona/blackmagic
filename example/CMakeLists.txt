add_custom_target(examples
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMENT "Build and run all the examples.")

macro(add_example Executable Source)
    add_executable(${Executable} EXCLUDE_FROM_ALL ${Source})
    add_test(NAME ${Executable} COMMAND ${Executable} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/example)
    add_dependencies(examples ${Executable})
endmacro(add_example)

add_example(regular_type "regular_type.cpp")
