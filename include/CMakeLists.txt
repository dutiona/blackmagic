set(BLACKMAGIC_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
add_library(Blackmagic INTERFACE)
target_compile_features(Blackmagic INTERFACE cxx_std_17)
target_include_directories(Blackmagic INTERFACE ${BLACKMAGIC_INCLUDE_DIR})

if(COMPILER_CLANG)
    target_compile_options(Blackmagic INTERFACE -Wno-gnu-string-literal-operator-template -frelaxed-template-template-args)
endif(COMPILER_CLANG)

# dummy static project not linked anywere needed so that a vcxproj is generated with the sources in the solution
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# Source listing
set(BLACKMAGIC_COMMON_SOURCES
        blackmagic/common/common.hpp
        blackmagic/common/dependent_false.hpp
        blackmagic/common/detector.hpp
        blackmagic/common/traits_ext.hpp
        blackmagic/common/tag_of.hpp
        blackmagic/common/utility.hpp
        blackmagic/common/common_reference.hpp
        blackmagic/common/sizeof.hpp)

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

set(BLACKMAGIC_CSTXPR_SOURCES
        blackmagic/cstxpr/algorithm.hpp
        blackmagic/cstxpr/cstxpr.hpp
        blackmagic/cstxpr/map.hpp
        blackmagic/cstxpr/vector.hpp
        blackmagic/cstxpr/algorithm/equal.hpp)

set(BLACKMAGIC_FUNCTIONAL_SOURCES
        blackmagic/functional/always.hpp
        blackmagic/functional/apply.hpp
        blackmagic/functional/arg.hpp
        blackmagic/functional/capture.hpp
        blackmagic/functional/compose.hpp
        blackmagic/functional/curry.hpp
        blackmagic/functional/demux.hpp
        blackmagic/functional/fix_point.hpp
        blackmagic/functional/flip.hpp
        blackmagic/functional/functional.hpp
        blackmagic/functional/identity.hpp
        blackmagic/functional/iterate.hpp
        blackmagic/functional/lockstep.hpp
        blackmagic/functional/on.hpp
        blackmagic/functional/overload.hpp
        blackmagic/functional/partial.hpp
        blackmagic/functional/placeholder.hpp
        blackmagic/functional/reverse_partial.hpp
        blackmagic/functional/utility.hpp
        blackmagic/functional/lazy/eval.hpp
        blackmagic/functional/lazy/eval_if.hpp
        blackmagic/functional/if.hpp
        blackmagic/functional/while.hpp
        blackmagic/functional/and.hpp
        blackmagic/functional/or.hpp
        blackmagic/functional/not.hpp
        blackmagic/functional/lazy/make_lazy.hpp
        blackmagic/functional/lazy.hpp
        blackmagic/integral/traits_ext.hpp)

set(BLACKMAGIC_INTEGRAL_SOURCES
        blackmagic/integral/integral.hpp
        blackmagic/integral/literals.hpp
        blackmagic/integral/operators.hpp
        blackmagic/integral/types.hpp
        blackmagic/integral/utility.hpp
        blackmagic/integral/operators/arithmetic.hpp
        blackmagic/integral/operators/logical.hpp
        blackmagic/integral/operators/comparison.hpp
        blackmagic/integral/functors.hpp
        blackmagic/integral/functors/increment.hpp
        blackmagic/integral/functors/decrement.hpp
        blackmagic/integral/functors/bit_and.hpp
        blackmagic/integral/functors/bit_lshift.hpp
        blackmagic/integral/functors/bit_not.hpp
        blackmagic/integral/functors/bit_or.hpp
        blackmagic/integral/functors/bit_rshift.hpp
        blackmagic/integral/functors/bit_xor.hpp
        blackmagic/integral/functors/decrement.hpp
        blackmagic/integral/functors/div.hpp
        blackmagic/integral/functors/equal.hpp
        blackmagic/integral/functors/greater_equal.hpp
        blackmagic/integral/functors/greater.hpp
        blackmagic/integral/functors/increment.hpp
        blackmagic/integral/functors/less_equal.hpp
        blackmagic/integral/functors/less.hpp
        blackmagic/integral/functors/logical_and.hpp
        blackmagic/integral/functors/logical_not.hpp
        blackmagic/integral/functors/logical_or.hpp
        blackmagic/integral/functors/minus.hpp
        blackmagic/integral/functors/mod.hpp
        blackmagic/integral/functors/mult.hpp
        blackmagic/integral/functors/negative.hpp
        blackmagic/integral/functors/not_equal.hpp
        blackmagic/integral/functors/plus.hpp
        blackmagic/integral/functors/positive.hpp
        blackmagic/integral/types/bool.hpp
        blackmagic/integral/types/char.hpp
        blackmagic/integral/types/int.hpp
        blackmagic/integral/types/long.hpp
        blackmagic/integral/types/long_long.hpp
        blackmagic/integral/types/short.hpp
        blackmagic/integral/types/size_t.hpp
        blackmagic/integral/types/unsigned_char.hpp
        blackmagic/integral/types/unsigned.hpp
        blackmagic/integral/types/unsigned_int.hpp
        blackmagic/integral/types/unsigned_long.hpp
        blackmagic/integral/types/unsigned_long_long.hpp
        blackmagic/integral/types/unsigned_short.hpp)

set(BLACKMAGIC_PAIR_SOURCES
        blackmagic/pair/algorithm.hpp
        blackmagic/pair/pair.hpp
        blackmagic/pair/utility.hpp
        blackmagic/pair/algorithm/flip.hpp
        blackmagic/pair/algorithm/flip_inplace.hpp)

set(BLACKMAGIC_TUPLE_SOURCES
        blackmagic/tuple/algorithm.hpp
        blackmagic/tuple/tuple.hpp
        blackmagic/tuple/utility.hpp
        blackmagic/tuple/ext/print.hpp
        blackmagic/tuple/ext/print_all.hpp
        blackmagic/tuple/ext/streamio.hpp
        blackmagic/tuple/algorithm/accumulate.hpp
        blackmagic/tuple/algorithm/all.hpp
        blackmagic/tuple/algorithm/all_of.hpp
        blackmagic/tuple/algorithm/any.hpp
        blackmagic/tuple/algorithm/any_of.hpp
        blackmagic/tuple/algorithm/at.hpp
        blackmagic/tuple/algorithm/back.hpp
        blackmagic/tuple/algorithm/contains.hpp
        blackmagic/tuple/algorithm/copy.hpp
        blackmagic/tuple/algorithm/copy_if.hpp
        blackmagic/tuple/algorithm/count.hpp
        blackmagic/tuple/algorithm/count_if.hpp
        blackmagic/tuple/algorithm/end.hpp
        blackmagic/tuple/algorithm/equal.hpp
        blackmagic/tuple/algorithm/filter.hpp
        blackmagic/tuple/algorithm/find.hpp
        blackmagic/tuple/algorithm/find_if.hpp
        blackmagic/tuple/algorithm/fold.hpp
        blackmagic/tuple/algorithm/fold_left.hpp
        blackmagic/tuple/algorithm/fold_right.hpp
        blackmagic/tuple/algorithm/for_each.hpp
        blackmagic/tuple/algorithm/front.hpp
        blackmagic/tuple/algorithm/length.hpp
        blackmagic/tuple/algorithm/merge.hpp
        blackmagic/tuple/algorithm/none.hpp
        blackmagic/tuple/algorithm/none_of.hpp
        blackmagic/tuple/algorithm/not_equal.hpp
        blackmagic/tuple/algorithm/pop_back.hpp
        blackmagic/tuple/algorithm/pop_front.hpp
        blackmagic/tuple/algorithm/push_back.hpp
        blackmagic/tuple/algorithm/push_front.hpp
        blackmagic/tuple/algorithm/remove.hpp
        blackmagic/tuple/algorithm/remove_if.hpp
        blackmagic/tuple/algorithm/repeat.hpp
        blackmagic/tuple/algorithm/replace.hpp
        blackmagic/tuple/algorithm/replace_if.hpp
        blackmagic/tuple/algorithm/reverse.hpp
        blackmagic/tuple/algorithm/rotate.hpp
        blackmagic/tuple/algorithm/rotate_left.hpp
        blackmagic/tuple/algorithm/rotate_right.hpp
        blackmagic/tuple/algorithm/sort.hpp
        blackmagic/tuple/algorithm/take.hpp
        blackmagic/tuple/algorithm/take_back.hpp
        blackmagic/tuple/algorithm/take_front.hpp
        blackmagic/tuple/algorithm/transform.hpp
        blackmagic/tuple/algorithm/unique.hpp
        blackmagic/tuple/algorithm/unpack.hpp
        blackmagic/tuple/algorithm/zip.hpp
        blackmagic/tuple/algorithm/details/filter_indexes.hpp)

set(BLACKMAGIC_TYPE_SOURCES
        blackmagic/type/conditionals.hpp
        blackmagic/type/helpers.hpp
        blackmagic/type/list.hpp
        blackmagic/type/type.hpp
        blackmagic/type/utility.hpp
        blackmagic/type/ext/print.hpp
        blackmagic/type/ext/streamio.hpp
        blackmagic/type/algorithm.hpp
        blackmagic/type/algorithm/details/merge_lists.hpp
        blackmagic/type/algorithm/all.hpp
        blackmagic/type/algorithm/all_of.hpp
        blackmagic/type/algorithm/any.hpp
        blackmagic/type/algorithm/any_of.hpp
        blackmagic/type/algorithm/none.hpp
        blackmagic/type/algorithm/none_of.hpp
        blackmagic/type/algorithm/back.hpp
        blackmagic/type/algorithm/count.hpp
        blackmagic/type/algorithm/count_if.hpp
        blackmagic/type/algorithm/front.hpp
        blackmagic/type/algorithm/merge.hpp
        blackmagic/type/algorithm/none.hpp
        blackmagic/type/algorithm/none_of.hpp
        blackmagic/type/algorithm/pop_back.hpp
        blackmagic/type/algorithm/pop_back_n.hpp
        blackmagic/type/algorithm/pop_front.hpp
        blackmagic/type/algorithm/pop_front_n.hpp
        blackmagic/type/algorithm/push_back.hpp
        blackmagic/type/algorithm/push_front.hpp
        blackmagic/type/algorithm/remove_if.hpp
        blackmagic/type/algorithm/sort.hpp
        blackmagic/type/algorithm/take_back.hpp
        blackmagic/type/algorithm/take_back_from.hpp
        blackmagic/type/algorithm/take_front.hpp
        blackmagic/type/algorithm/take_front_from.hpp
        blackmagic/type/algorithm/unique.hpp
        blackmagic/type/algorithm/at.hpp)

set(BLACKMAGIC_SOURCES
        blackmagic/blackmagic.hpp
        ${BLACKMAGIC_COMMON_SOURCES}
        ${BLACKMAGIC_CONCEPTS_SOURCES}
        ${BLACKMAGIC_CSTXPR_SOURCES}
        ${BLACKMAGIC_FUNCTIONAL_SOURCES}
        ${BLACKMAGIC_INTEGRAL_SOURCES}
        ${BLACKMAGIC_PAIR_SOURCES}
        ${BLACKMAGIC_TUPLE_SOURCES}
        ${BLACKMAGIC_TYPE_SOURCES})

add_library(Blackmagic_srcs EXCLUDE_FROM_ALL STATIC ${BLACKMAGIC_SOURCES})
set_target_properties(Blackmagic_srcs PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(Blackmagic_srcs PUBLIC cxx_std_17)
target_link_libraries(Blackmagic_srcs PUBLIC Blackmagic)
source_group(TREE ${BLACKMAGIC_INCLUDE_DIR} FILES ${BLACKMAGIC_SOURCES})


