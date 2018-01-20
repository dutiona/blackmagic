cmake_minimum_required(VERSION 3.8.2) # required for cxx_std_17

project(Metaprog VERSION 0.0.1 LANGUAGES CXX)

set(METAPROG_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

if(MSVC OR APPLE)
#dummy static project not linked anywere needed so that a vcxproj is generated with the sources in the solution
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    file(GLOB_RECURSE METAPROG_SOURCES  "${METAPROG_INCLUDE_DIR}/*.hpp")
    add_library(Metaprog_srcs STATIC ${METAPROG_SOURCES})
    set_target_properties(Metaprog_srcs PROPERTIES LINKER_LANGUAGE CXX)
    target_compile_features(Metaprog_srcs PUBLIC cxx_std_17)
    target_include_directories(Metaprog_srcs PUBLIC ${METAPROG_INCLUDE_DIR})
    source_group(TREE ${METAPROG_INCLUDE_DIR} FILES ${METAPROG_SOURCES})
endif()

add_library(Metaprog INTERFACE)
target_compile_features(Metaprog INTERFACE cxx_std_17)
#target_link_libraries(Metaprog INTERFACE stdc++) #gcc for mac needs - lstdc++
target_include_directories(Metaprog INTERFACE ${METAPROG_INCLUDE_DIR})



if(MSVC)
#MSVC
    add_compile_options(/W4 /WX /permissive- /std:c++17)
#Clang / C2
#add_compile_options(-Wall - Werror - pedantic)
else(MSVC)
    add_compile_options(-Wall -Wextra -Werror -pedantic)
#add_compile_options(-Wall - Wextra - Werror - pedantic)
endif(MSVC)

install(DIRECTORY include DESTINATION include FILES_MATCHING PATTERN "*.hpp")

add_subdirectory(example)

add_subdirectory(benchmark)

enable_testing()
add_subdirectory(test)

#Setup the `check` convenience target, which is equivalent to examples + tests.
add_custom_target(check
    DEPENDS examples tests benchmarks
    COMMENT "Build and run all the unit tests and examples.")
