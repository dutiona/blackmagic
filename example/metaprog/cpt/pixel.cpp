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



template <typename PixelType>
using value_type_construct = typename PixelType::value_type;
template <typename PixelType>
using reference_construct  = typename PixelType::reference;
template <typename PixelType>
using point_type_construct = typename PixelType::point_type;
template <typename PixelType>
using site_type_construct  = typename PixelType::site_type;
template <typename PixelType>
using image_type_construct = typename PixelType::image_type;


inline constexpr auto PixelConstructs =
  concepts::valid_exprs<value_type_construct, reference_construct, site_type_construct, image_type_construct>("PixelConstructs"sv);

// point_type alias site_type
inline constexpr auto PointType_Is_SiteType =
  concepts::make_concept_map(PixelConstructs, concepts::same<point_type_construct, site_type_construct>("PointType_Is_SiteType"sv));


// value type is not reference
template <typename PixelType>
using value_type_is_not_a_reference = std::negation<std::is_reference<value_type_construct<PixelType>>>;

inline constexpr auto ValueType_IsNotA_Reference = concepts::make_concept_map(
  PixelConstructs, concepts::is_true<value_type_is_not_a_reference>("ValueType_IsNotA_Reference"sv));


// has method point
template <typename PixelType>
using method_val = decltype(std::declval<PixelType>().val());
template <typename PixelType>
using method_point = decltype(std::declval<PixelType>().point());
template <typename PixelType>
using method_site = decltype(std::declval<PixelType>().site());
template <typename PixelType>
using method_image = decltype(std::declval<PixelType>().image());

inline constexpr auto HasMethods = concepts::make_concept_map(
    PixelConstructs,
    concepts::valid_exprs<method_val, method_point, method_site, method_image>("HasMethods"sv),
    concepts::convertible_to<method_val, reference_construct>("Method_val_Returns_reference"sv),
    concepts::convertible_to<method_point, point_type_construct>("Method_point_Returns_point"sv),
    concepts::convertible_to<method_site, site_type_construct>("Method_site_Returns_site_type"sv),
    concepts::convertible_to<method_image, image_type_construct>("Method_image_Returns_image_type"sv)
);

} // namespace pixel_concept_traits

inline constexpr auto Pixel =
  concepts::make_concept_map(pixel_concept_traits::PixelConstructs, pixel_concept_traits::PointType_Is_SiteType,
                             pixel_concept_traits::ValueType_IsNotA_Reference , pixel_concept_traits::HasMethods);

namespace concept_diagnostic_traits {

template <typename PixelType>
constexpr void diagnostic(decltype(Pixel))
{
  static_assert(Pixel.check_at<PixelType>("PixelConstructs"sv), "PixelConstructs attribute missing");

  static_assert(Pixel.check_at<PixelType>("PointType_Is_SiteType"sv), "point_type should alias site_type");
  static_assert(Pixel.check_at<PixelType>("ValueType_IsNotA_Reference"sv), "value_type should not be a reference");

  static_assert(Pixel.check_at<PixelType>("HasMethods"sv), "methods missing or ill-defined");
  static_assert(Pixel.check_at<PixelType>("Method_val_Returns_reference"sv), "method val's return type is wrong");
  static_assert(Pixel.check_at<PixelType>("Method_point_Returns_point"sv), "method point's return type is wrong");
  static_assert(Pixel.check_at<PixelType>("Method_site_Returns_site_type"sv), "method site's return type is wrong");
  static_assert(Pixel.check_at<PixelType>("Method_image_Returns_image_type"sv), "method image's return type is wrong");
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

// Vérification
static_assert(Pixel.check<MyPixel>(), "MyPixel doesn't model the Pixel concept!");
static_assert(!Pixel.check<MyBadPixel>(), "MyBadPixel modeld the Pixel concept!");


/*
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
