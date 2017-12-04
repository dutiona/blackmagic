add_custom_target(examples
    COMMENT "Build and run all the examples.")

macro(add_example Executable Source)
    add_executable(example_${Executable}.exe EXCLUDE_FROM_ALL ${Source})

    target_link_libraries(example_${Executable}.exe PRIVATE Concepts)
    target_include_directories(example_${Executable}.exe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    add_custom_target(example_${Executable}
        COMMAND example_${Executable}.exe
        DEPENDS example_${Executable}.exe
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/example
        USES_TERMINAL)
        
    add_dependencies(examples example_${Executable})
endmacro(add_example)

option(WITH_EXAMPLES "Compile and run examples" OFF)

if(WITH_EXAMPLES)
    
    add_example(regular_type "regular_type.cpp")
    
endif(WITH_EXAMPLES)
