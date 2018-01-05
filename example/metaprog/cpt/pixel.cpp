#include <metaprog/cpt/cpt.hpp>

#include <type_traits>
#include <utility>
#include <string_view>

using namespace std::literals;
namespace concepts = cpt::concepts;

template<typename...>
struct _parameters_pack {
};

template <bool SilentFailure, template<typename...>class Contraint, typename Holder, typename = void>
struct custom_concept_impl : std::false_type {
  static_assert(SilentFailure, "Custom concept failed");
};

template <bool SilentFailure, template<typename...>class Constraint, template<typename...> class ParametersPack, typename... Parameters>
struct custom_concept_impl<SilentFailure, Constraint, ParametersPack<Parameters...>, std::void_t<Constraint<Parameters...>>> : std::true_type {
};

template<template<typename...> class Constraint>
struct custom_concept {
  template <bool SilentFailure, typename... Parameters>
  using type = custom_concept_impl<SilentFailure, Constraint, _parameters_pack<Parameters...>>;
  template <bool SilentFailure, typename... Parameters>
  using underlying_type = typename type<SilentFailure, Parameters...>::type;
  template <bool SilentFailure, typename... Parameters>
  static constexpr bool value = type<SilentFailure, Parameters...>::value;
};


namespace pixel_concept { namespace traits {

template<typename PixelType>
using has_value_type = typename PixelType::value_type;

constexpr auto value_type_concept_item  = cpt::make_concept_item<custom_concept<has_value_type>>("value_type_concept"sv);

}

constexpr auto pixel = cpt::make_concept_map(traits::value_type_concept_item);

}

struct MyPixel {
  using value_type = void;
};

struct MyBadPixel {
  using ValueType = void;
};

static_assert(cpt::check_map<MyPixel>(pixel_concept::pixel), "Check concept map for MyPixel");
static_assert(!cpt::check_map<MyBadPixel>(pixel_concept::pixel), "Check concept map for MyBadPixel");

/*
template<typename PixelType>
using has_value_type = typename PixelType::value_type;

using value_type_concept = custom_concept<has_value_type>;

static_assert(cpt::check<value_type_concept, MyPixel>(), "Check concept map for MyPixel");
 */


int main()
{
  return 0;
}
