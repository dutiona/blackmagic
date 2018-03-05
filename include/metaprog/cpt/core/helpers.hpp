#pragma once

#ifndef METAPROG_CPT_CORE_HELPERS_HPP_
#define METAPROG_CPT_CORE_HELPERS_HPP_

#include "../../type/type.hpp"

#include <type_traits>

namespace cpt::helpers {

// traits helper
namespace details {

template <typename Holder, typename = void>
struct make_trait_from_constructs_impl : std::false_type {
};
template <template <typename... Constraints> class Holder, typename... Constraints>
struct make_trait_from_constructs_impl<Holder<Constraints...>, std::void_t<Constraints...>> : std::true_type {
};

template <typename Holder, typename = void>
struct make_trait_from_predicates_impl : std::false_type {
};
template <template <typename... Predicates> class Holder, typename... Predicates>
struct make_trait_from_predicates_impl<Holder<Predicates...>, std::enable_if_t<std::conjunction_v<Predicates...>>>
  : std::true_type {
};

} // namespace details

template <typename... Constraints>
using make_trait_from_constructs = details::make_trait_from_constructs_impl<type::basic_type_holder<Constraints...>>;

template <typename... Predicates>
using make_trait_from_predicates = details::make_trait_from_predicates_impl<type::basic_type_holder<Predicates...>>;

// TODO/FIXME investigate this issue.
// We can't use :
// template <typename T>
// struct is_mytrait : helpers::make_trait_from_constructs<decltype(...<T>...)> {};
// yet because it's not a SFINAE context... :(
// Maybe in a fully fledge c++17/20 compiler with the extension of SFINAE context...
// Or maybe it's a compiler bug.


// concept helpers
namespace details {

template <bool SilentFailure, template <typename...> class Constraint, typename ParametersPack, typename = void>
struct make_concept_from_construct_impl : std::false_type {
  static_assert(SilentFailure, "Concept checking failed. Use diagnostic to have more detailed about the failure.");
};

template <bool SilentFailure, template <typename...> class Constraint, template <typename...> class ParametersPack,
          typename... Parameters>
struct make_concept_from_construct_impl<SilentFailure, Constraint, ParametersPack<Parameters...>,
                                        std::void_t<Constraint<Parameters...>>> : std::true_type {
};

template <bool SilentFailure, template <typename...> class Predicate, typename ParametersPack, typename = void>
struct make_concept_from_predicate_impl : std::false_type {
  static_assert(SilentFailure, "Concept checking failed. Use diagnostic to have more detailed about the failure.");
};

template <bool SilentFailure, template <typename...> class Predicate, template <typename...> class ParametersPack,
          typename... Parameters>
struct make_concept_from_predicate_impl<SilentFailure, Predicate, ParametersPack<Parameters...>,
                                        std::enable_if_t<Predicate<Parameters...>::value>> : std::true_type {
};

} // namespace details

template <template <typename...> class Constraint>
struct make_concept_from_construct {
  template <bool SilentFailure, typename... Parameters>
  using type =
    details::make_concept_from_construct_impl<SilentFailure, Constraint, type::basic_type_holder<Parameters...>>;
  template <bool SilentFailure, typename... Parameters>
  using underlying_type = typename type<SilentFailure, Parameters...>::type;
  template <bool SilentFailure, typename... Parameters>
  static constexpr bool value = type<SilentFailure, Parameters...>::value;
};

template <template <typename...> class Predicate>
struct make_concept_from_predicate {
  template <bool SilentFailure, typename... Parameters>
  using type =
    details::make_concept_from_predicate_impl<SilentFailure, Predicate, type::basic_type_holder<Parameters...>>;
  template <bool SilentFailure, typename... Parameters>
  using underlying_type = typename type<SilentFailure, Parameters...>::type;
  template <bool SilentFailure, typename... Parameters>
  static constexpr bool value = type<SilentFailure, Parameters...>::value;
};


} // namespace cpt::helpers


#endif // METAPROG_CPT_CORE_HELPERS_HPP_
