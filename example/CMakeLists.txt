add_custom_target(examples-compile ALL COMMENT "Build all the examples.")

add_custom_target(examples EXCLUDE_FROM_ALL
        DEPENDS examples-compile
        COMMENT "Build and run all the examples.")

macro(add_example Executable)
    set(Sources ${ARGN})
    add_executable(example_${Executable} EXCLUDE_FROM_ALL ${Sources})

    target_link_libraries(example_${Executable} PRIVATE Blackmagic)
    target_include_directories(example_${Executable} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    add_dependencies(examples-compile example_${Executable})

    add_custom_target(example_${Executable}_run
        COMMAND example_${Executable}
        DEPENDS example_${Executable}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/example
        USES_TERMINAL)

    add_dependencies(examples example_${Executable}_run)
endmacro(add_example)

option(WITH_EXAMPLES "Compile and run examples" OFF)

if(WITH_EXAMPLES)
    
    add_subdirectory(blackmagic)
    
endif(WITH_EXAMPLES)
