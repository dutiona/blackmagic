#include <metaprog/concepts/concepts.hpp>

#include <string_view>

using namespace std::literals;
namespace concepts = metaprog::concepts;

namespace pixel_concept_traits {

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
  concepts::make_concept_map(pixel_concept_traits::PixelConstructs/*, pixel_concept_traits::PointType_Is_SiteType,
                             pixel_concept_traits::ValueType_IsNot_Reference, pixel_concept_traits::HasMethods*/);

namespace concept_diagnostic_traits {

template <typename PixelType>
constexpr void diagnostic(decltype(Pixel))
{
  static_assert(Pixel.check_at<PixelType>("PixelConstructs"sv), "PixelConstructs attribute missing");

  static_assert(Pixel.check_at<PixelType>("PointType_Is_SiteType"sv), "point_type should alias site_type");
  //static_assert(Pixel.check_at<PixelType>("ValueType_IsNot_Reference"sv), "value_type should not be a reference");

  //static_assert(Pixel.check_at<PixelType>("HasMethods"sv), "methods missing or ill-defined");
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

int main()
{
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
