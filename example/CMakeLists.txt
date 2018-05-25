add_custom_target(examples-compile ALL COMMENT "Build all the examples.")

add_custom_target(examples EXCLUDE_FROM_ALL
        DEPENDS examples-compile
        COMMENT "Build and run all the examples.")

macro(add_example Executable Source)
    add_executable(example_${Executable}.exe EXCLUDE_FROM_ALL ${Source})

    target_link_libraries(example_${Executable}.exe PRIVATE Blackmagic)
    target_include_directories(example_${Executable}.exe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    add_dependencies(examples-compile example_${Executable}.exe)

    add_custom_target(example_${Executable}
        COMMAND example_${Executable}.exe
        DEPENDS example_${Executable}.exe
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/example
        USES_TERMINAL)

    add_dependencies(examples example_${Executable})
endmacro(add_example)

option(WITH_EXAMPLES "Compile and run examples" OFF)

if(WITH_EXAMPLES)
    
    add_subdirectory(blackmagic)
    
endif(WITH_EXAMPLES)
