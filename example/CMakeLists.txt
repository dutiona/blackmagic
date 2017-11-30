add_custom_target(examples
    COMMENT "Build and run all the examples.")

macro(add_example Executable Source)
    add_executable(example_${Executable}.exe EXCLUDE_FROM_ALL ${Source})
    add_custom_target(example_${Executable}
        COMMAND example_${Executable}.exe
        DEPENDS example_${Executable}.exe
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/example
        USES_TERMINAL)
    add_dependencies(examples example_${Executable})
endmacro(add_example)

add_example(regular_type "regular_type.cpp")
