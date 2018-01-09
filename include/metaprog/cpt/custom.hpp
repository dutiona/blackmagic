#pragma once

#ifndef METAPROG_CPT_CUSTOM_HPP_
#define METAPROG_CPT_CUSTOM_HPP_

#include <type_traits>

namespace cpt {

namespace details {
template <typename...>
struct _parameters_pack {
};

template <bool SilentFailure, template <typename...> class Constraint, typename Holder, typename = void>
struct make_custom_concept_from_construct_impl : std::false_type {
  static_assert(SilentFailure, "Concept checking failed. Use diagnostic to have more detailed about the failure.");
};

template <bool SilentFailure, template <typename...> class Constraint, template <typename...> class ParametersPack,
          typename... Parameters>
struct make_custom_concept_from_construct_impl<SilentFailure, Constraint, ParametersPack<Parameters...>,
                                               std::void_t<Constraint<Parameters...>>> : std::true_type {
};

template <bool SilentFailure, template <typename...> class Predicate, typename Holder, typename = void>
struct make_custom_concept_from_predicate_impl : std::false_type {
  static_assert(SilentFailure, "Concept checking failed. Use diagnostic to have more detailed about the failure.");
};

template <bool SilentFailure, template <typename...> class Predicate, template <typename...> class ParametersPack,
          typename... Parameters>
struct make_custom_concept_from_predicate_impl<SilentFailure, Predicate, ParametersPack<Parameters...>,
                                               std::enable_if_t<Predicate<Parameters...>::value>> : std::true_type {
};
} // namespace details

template <template <typename...> class Constraint>
struct make_custom_concept_from_construct {
  template <bool SilentFailure, typename... Parameters>
  using type = details::make_custom_concept_from_construct_impl<SilentFailure, Constraint,
                                                                details::_parameters_pack<Parameters...>>;
  template <bool SilentFailure, typename... Parameters>
  using underlying_type = typename type<SilentFailure, Parameters...>::type;
  template <bool SilentFailure, typename... Parameters>
  static constexpr bool value = type<SilentFailure, Parameters...>::value;
};

template <template <typename...> class Predicate>
struct make_custom_concept_from_predicate {
  template <bool SilentFailure, typename... Parameters>
  using type = details::make_custom_concept_from_predicate_impl<SilentFailure, Predicate,
                                                                details::_parameters_pack<Parameters...>>;
  template <bool SilentFailure, typename... Parameters>
  using underlying_type = typename type<SilentFailure, Parameters...>::type;
  template <bool SilentFailure, typename... Parameters>
  static constexpr bool value = type<SilentFailure, Parameters...>::value;
};

template <typename... Bs>
using make_predicate = std::conjunction<Bs...>;

template <bool B>
using make_condition = std::bool_constant<B>;

} // namespace cpt

#endif // METAPROG_CPT_CUSTOM_HPP_
