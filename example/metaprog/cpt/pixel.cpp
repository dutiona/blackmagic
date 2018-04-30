#include <metaprog/concepts/concepts.hpp>

#include <iostream>
#include <string>
#include <string_view>

using namespace std::literals;
namespace concepts = metaprog::concepts;

namespace pixel_concept_traits {


template <typename T>
struct S {
  std::string_view s_;
  using type = T;
  constexpr S(std::string_view s)
    : s_(s)
  {
  }
};

template <typename T, typename U>
constexpr bool operator==(const S<T>& lhs, const S<U>& rhs)
{
  return lhs.s_ == rhs.s_;
}

static_assert(metaprog::tuple::front(std::make_tuple("lol"sv, 6.0)) == "lol"sv);
static_assert(metaprog::tuple::back(std::make_tuple("lol"sv, 6.0)) == 6.0, "");
static_assert(metaprog::tuple::equals(metaprog::tuple::push_front(std::make_tuple("lol"sv), 6.0),
                                      std::make_tuple(6.0, "lol"sv)));
static_assert(metaprog::tuple::equals(metaprog::tuple::push_back(std::make_tuple("lol"sv), 6.0),
                                      std::make_tuple("lol"sv, 6.0)));
static_assert(metaprog::tuple::equals(metaprog::tuple::pop_front(std::make_tuple("lol"sv, 6.0)), std::make_tuple(6.0)));
static_assert(metaprog::tuple::equals(metaprog::tuple::pop_back(std::make_tuple("lol"sv, 6.0)),
                                      std::make_tuple("lol"sv)));
static_assert(metaprog::tuple::equals(metaprog::tuple::rotate_left(std::make_tuple("lol"sv, 6.0, 4)),
                                      std::make_tuple(6.0, 4, "lol"sv)));
static_assert(metaprog::tuple::equals(metaprog::tuple::rotate_right(std::make_tuple("lol"sv, 6.0, 4)),
                                      std::make_tuple(4, "lol"sv, 6.0)));


static_assert(metaprog::tuple::equals(std::make_tuple(0, 1, 4.0, 5.0, "lol"sv),
                                      metaprog::tuple::reverse(std::make_tuple("lol"sv, 5.0, 4.0, 1, 0))));

static_assert(metaprog::tuple::fold_left(std::make_tuple(10, 2), [](auto lhs, auto rhs) { return lhs / rhs; }) == 5);

static_assert(metaprog::tuple::fold_left(std::make_tuple(2, 2, 1), [](auto lhs, auto rhs) { return lhs / rhs; }, 20)
              == 5);

static_assert(metaprog::tuple::fold_right(std::make_tuple(2, 10), [](auto lhs, auto rhs) { return lhs / rhs; }) == 5);

static_assert(metaprog::tuple::fold_right(std::make_tuple(2, 2), [](auto lhs, auto rhs) { return lhs / rhs; }, 1, 20)
              == 5);

static_assert(metaprog::tuple::unpack(std::make_tuple(1, 2, 3, 4, 5), [](auto... x) { return (x + ...); }) == 15);

inline constexpr int t[] = {1, 2, 3, 4, 5};
static_assert(metaprog::tuple::unpack(t, [](auto... x) { return (x + ...); }) == 15);


static_assert(metaprog::tuple::equals(metaprog::tuple::filter<std::is_integral>(std::make_tuple(1, 2.0, 3, 4.0, 5)),
                                      std::make_tuple(1, 3, 5)));

/*
static_assert(metaprog::tuple::equals(metaprog::tuple::filter(std::make_tuple(1, 2.0, 3, 48.0, 55),
                                                              [](auto a) { return std::is_integral_v<decltype(a)>; }),
                                      std::make_tuple(0, -1, 2, -1, 4)));

*/

inline constexpr auto Test = std::make_tuple(S<int>("int"sv), S<double>("double"sv), S<int>("int"sv));

inline constexpr auto tt = std::tuple_cat(Test, Test);

static_assert(std::get<0>(Test) == S<int>("int"sv), "");
static_assert(std::get<1>(Test) == S<double>("double"sv), "");
static_assert(std::get<2>(Test) == S<int>("int"sv), "");

// inline constexpr auto Test_unique = metaprog::tuple::unique(Test);


template <typename PixelType>
struct pixel_constructs {
  using value_type_construct = typename PixelType::value_type;
  using reference_construct  = typename PixelType::reference;
  using point_type_construct = typename PixelType::point_type;
  using site_type_construct  = typename PixelType::site_type;
  using image_type_construct = typename PixelType::image_type;
};

inline constexpr auto PixelConstructs = concepts::valid_expr<pixel_constructs>("PixelConstructs"sv);

// point_type alias site_type
template <typename PixelType>
using point_type = typename PixelType::point_type;
template <typename PixelType>
using site_type = typename PixelType::site_type;

inline constexpr auto PointType_Is_SiteType =
  concepts::make_concept_map(PixelConstructs, concepts::same<point_type, site_type>("PointType_Is_SiteType"sv));
/*
// value type is not reference
template <typename PixelType>
using value_type_is_not_a_reference_predicate = concepts::make_predicate<
  concepts::make_condition<PixelConstructs.check<PixelType>()>,
  concepts::make_condition<!std::is_reference_v<typename pixel_constructs<PixelType>::value_type_construct>>>;
inline constexpr auto ValueType_IsNot_Reference =
  concepts::make_concept_item_from_predicate<value_type_is_not_a_reference_predicate>("ValueType_IsNot_Reference"sv);

// has method point
template <typename PixelType>
using has_methods_predicate = concepts::make_predicate<
  concepts::make_condition<PixelConstructs.check<PixelType>()>,
  concepts::valid_expr<
    decltype(concepts::convertible_to<typename PixelType::reference>(std::declval<PixelType>().val())),
    decltype(concepts::convertible_to<typename PixelType::point_type>(std::declval<PixelType>().point())),
    decltype(concepts::convertible_to<typename PixelType::site_type>(std::declval<PixelType>().site())),
    decltype(concepts::convertible_to<typename PixelType::image_type>(std::declval<PixelType>().image()))>>;
inline constexpr auto HasMethods = concepts::make_concept_item_from_predicate<has_methods_predicate>("HasMethods"sv);
*/
} // namespace pixel_concept_traits

inline constexpr auto Pixel =
  concepts::make_concept_map(pixel_concept_traits::PixelConstructs, pixel_concept_traits::PointType_Is_SiteType/*,
                             pixel_concept_traits::ValueType_IsNot_Reference, pixel_concept_traits::HasMethods*/);

namespace concept_diagnostic_traits {

template <typename PixelType>
constexpr void diagnostic(decltype(Pixel))
{
  static_assert(Pixel.check_at<PixelType>("PixelConstructs"sv), "PixelConstructs attribute missing");

  static_assert(Pixel.check_at<PixelType>("PointType_Is_SiteType"sv), "point_type should alias site_type");
  // static_assert(Pixel.check_at<PixelType>("ValueType_IsNot_Reference"sv), "value_type should not be a reference");

  // static_assert(Pixel.check_at<PixelType>("HasMethods"sv), "methods missing or ill-defined");
}

} // namespace concept_diagnostic_traits


struct MyPixel {
  using value_type = int;
  using reference  = int&;
  using point_type = double;
  using site_type  = double;
  using image_type = void*;

  reference  val();
  point_type point();
  site_type  site();
  image_type image();
};

struct MyBadPixel {
  using value_type = int&; // should not be a ref
  using reference  = int&;
  using point_type = double; // point_type & site_type should be aliases
  using site_type  = int;
  using image_type = void*;

  reference  val();
  point_type point();
  site_type  site();
  image_type image();
};


namespace details {
template <typename... Ts, size_t... I>
void print_tuple(const std::tuple<Ts...>& tpl, std::index_sequence<I...>)
{
  ((std::cout << "[" << I << "] : " << std::get<I>(tpl) << '\n'), ...);
}
} // namespace details
template <typename... Ts>
void print_tuple(const std::tuple<Ts...>& tpl)
{
  details::print_tuple(tpl, std::index_sequence_for<Ts...>{});
}

// Vérification
static_assert(Pixel.check<MyPixel>(), "MyPixel doesn't model the Pixel concept!");

/*
inline constexpr auto tpl = std::make_tuple(1, 2.0, 3, 48.0, 55);
inline constexpr auto ret = metaprog::tuple::filter<std::is_integral>(tpl);
*/


int main()
{
  /*
  print_tuple(metaprog::tuple::filter<std::is_integral>(std::make_tuple(1, 2.0, 3, 48.0, 55)));
  print_tuple(metaprog::tuple::remove_if<std::is_integral>(std::make_tuple(1, 2.0, 3, 48.0, 55)));
  print_tuple(metaprog::tuple::remove_if<std::is_same, int>(std::make_tuple(1, 2.0, 3, 48.0, 55)));
  print_tuple(metaprog::tuple::unique(std::make_tuple(1, 2.0, 3, 48.0, 55)));
  */
  /*
  if constexpr (!Pixel.check<MyPixel>()) {
    DIAGNOSTIC(Pixel, MyPixel);
  }
  if constexpr (!Pixel.check<MyBadPixel>()) {
    // DIAGNOSTIC(Pixel, MyBadPixel);
  }
   */

  return 0;
}
