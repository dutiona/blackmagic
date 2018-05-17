set(BLACKMAGIC_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
add_library(Blackmagic INTERFACE)
target_compile_features(Blackmagic INTERFACE cxx_std_17)
target_include_directories(Blackmagic INTERFACE ${BLACKMAGIC_INCLUDE_DIR})

# dummy static project not linked anywere needed so that a vcxproj is generated with the sources in the solution
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# Source listing

file(GLOB_RECURSE BLACKMAGIC_SOURCES  "${BLACKMAGIC_INCLUDE_DIR}/*.hpp")

set(BLACKMAGIC_COMMON_SOURCES
        blackmagic/common/common.hpp
        blackmagic/common/dependent_false.hpp
        blackmagic/common/detector.hpp
        blackmagic/common/traits_ext.hpp
        blackmagic/common/algorithm.hpp
        blackmagic/common/algorithm/all_of_v.hpp
        blackmagic/common/algorithm/any_of_v.hpp
        blackmagic/common/algorithm/are_equal.hpp
        blackmagic/common/algorithm/are_not_equal.hpp
        blackmagic/common/algorithm/count_v.hpp
        blackmagic/common/algorithm/none_of_v.hpp)

set(BLACKMAGIC_CONCEPTS_SOURCES
        blackmagic/concepts/concepts.hpp
        blackmagic/concepts/engine.hpp
        blackmagic/concepts/basic/concepts.hpp
        blackmagic/concepts/basic/traits.hpp
        blackmagic/concepts/engine/checker.hpp
        blackmagic/concepts/engine/diagnostic.hpp
        blackmagic/concepts/engine/item.hpp
        blackmagic/concepts/engine/map.hpp
        blackmagic/concepts/engine/utility.hpp
        blackmagic/concepts/layout/concepts.hpp
        blackmagic/concepts/layout/traits.hpp
        blackmagic/concepts/utility/concepts.hpp
        blackmagic/concepts/utility/traits.hpp
        blackmagic/concepts/utility/details/traits_impl.hpp)

set(BLACKMAGIC_CONCEPTS_SOURCES
        blackmagic/concepts/concepts.hpp
        blackmagic/concepts/engine.hpp
        blackmagic/concepts/basic/concepts.hpp
        blackmagic/concepts/basic/traits.hpp
        blackmagic/concepts/engine/checker.hpp
        blackmagic/concepts/engine/diagnostic.hpp
        blackmagic/concepts/engine/item.hpp
        blackmagic/concepts/engine/map.hpp
        blackmagic/concepts/engine/utility.hpp
        blackmagic/concepts/layout/concepts.hpp
        blackmagic/concepts/layout/traits.hpp
        blackmagic/concepts/utility/concepts.hpp
        blackmagic/concepts/utility/traits.hpp
        blackmagic/concepts/utility/details/traits_impl.hpp)

#set(BLACKMAGIC_SOURCES
#        blackmagic/blackmagic.hpp
#        ${BLACKMAGIC_COMMON_SOURCES}
#        ${BLACKMAGIC_CONCEPTS_SOURCES}
#        ${BLACKMAGIC_CSTXPR_SOURCES}
#        ${BLACKMAGIC_FUNCTIONAL_SOURCES}
#        ${BLACKMAGIC_INTEGRAL_SOURCES}
#        ${BLACKMAGIC_PAIR_SOURCES}
#        ${BLACKMAGIC_TUPLE_SOURCES}
#        ${BLACKMAGIC_TUPLE_SOURCES})

add_library(Blackmagic_srcs EXCLUDE_FROM_ALL STATIC ${BLACKMAGIC_SOURCES})
set_target_properties(Blackmagic_srcs PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(Blackmagic_srcs PUBLIC cxx_std_17)
target_include_directories(Blackmagic_srcs PUBLIC ${BLACKMAGIC_INCLUDE_DIR})
source_group(TREE ${BLACKMAGIC_INCLUDE_DIR} FILES ${BLACKMAGIC_SOURCES})


