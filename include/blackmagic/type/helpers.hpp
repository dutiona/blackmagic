#pragma once

namespace metaprog::type::helpers {

// Call metafunc

template <typename MetaFunc, typename... Args>
struct call {
  using type = typename MetaFunc::template type<Args...>;
};
template <typename MetaFunc>
struct call<MetaFunc> {
  using type = typename MetaFunc::type;
};

template <typename MetaFunc, typename... Args>
using call_t = typename call<MetaFunc, Args...>::type;

// Check metafunc

template <typename MetaFunc, typename... Args>
struct check {
  static constexpr auto value = MetaFunc::template value<Args...>;
};
template <typename MetaFunc>
struct check<MetaFunc> {
  static constexpr auto value = MetaFunc::value;
};

template <typename MetaFunc, typename... Args>
inline constexpr auto check_v = check<MetaFunc, Args...>::value;

// Trait helper

template <template <typename...> class Trait, typename... Args>
struct make_type_from_trait {
  template <typename... Params>
  using type = typename Trait<Args..., Params...>::type;
};

template <template <typename...> class Trait, typename... Args>
struct make_value_from_trait {
  template <typename... Params>
  static constexpr auto value = Trait<Args..., Params...>::value;
};

template <template <typename...> class Trait, typename... Args>
struct make_both_from_trait {
  template <typename... Params>
  using type = typename Trait<Args..., Params...>::type;

  template <typename... Params>
  static constexpr auto value = Trait<Args..., Params...>::value;
};

} // namespace blackmagic::type::helpers
