#pragma once

#ifndef METAPROG_CPT_CUSTOM_HPP_
#define METAPROG_CPT_CUSTOM_HPP_

#include <type_traits>
#include <utility>

namespace cpt {

namespace details {
template <typename...>
struct _parameters_pack {
};

template <bool SilentFailure, template <typename...> class Contraint, typename Holder, typename = void>
struct custom_concept_impl : std::false_type {
  static_assert(SilentFailure, "Custom concept failed");
};

template <bool SilentFailure, template <typename...> class Constraint, template <typename...> class ParametersPack,
          typename... Parameters>
struct custom_concept_impl<SilentFailure, Constraint, ParametersPack<Parameters...>,
                           std::void_t<Constraint<Parameters...>>> : std::true_type {
};
} // namespace details

template <template <typename...> class Constraint>
struct custom_concept {
  template <bool SilentFailure, typename... Parameters>
  using type = details::custom_concept_impl<SilentFailure, Constraint, details::_parameters_pack<Parameters...>>;
  template <bool SilentFailure, typename... Parameters>
  using underlying_type = typename type<SilentFailure, Parameters...>::type;
  template <bool SilentFailure, typename... Parameters>
  static constexpr bool value = type<SilentFailure, Parameters...>::value;
};

} // namespace cpt

#endif // METAPROG_CPT_CUSTOM_HPP_
