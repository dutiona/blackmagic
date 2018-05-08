#include <blackmagic/concepts/concepts.hpp>

#include <string_view>

using namespace std::literals;

namespace concepts = metaprog::concepts;

namespace pixel_concept_traits {

template <typename PixelType>
using value_type_construct = typename PixelType::value_type;
template <typename PixelType>
using reference_construct = typename PixelType::reference;
template <typename PixelType>
using point_type_construct = typename PixelType::point_type;
template <typename PixelType>
using site_type_construct = typename PixelType::site_type;
template <typename PixelType>
using image_type_construct = typename PixelType::image_type;


inline constexpr auto PixelConstructs =
  concepts::valid_exprs<value_type_construct, reference_construct, site_type_construct, image_type_construct>(
    "PixelConstructs"sv);

// point_type alias site_type
inline constexpr auto PointType_Is_SiteType = concepts::make_concept_map(
  PixelConstructs, concepts::same<point_type_construct, site_type_construct>("PointType_Is_SiteType"sv));


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
  PixelConstructs, concepts::valid_exprs<method_val, method_point, method_site, method_image>("HasMethods"sv),
  concepts::convertible_to<method_val, reference_construct>("Method_val_Returns_reference"sv),
  concepts::convertible_to<method_point, point_type_construct>("Method_point_Returns_point"sv),
  concepts::convertible_to<method_site, site_type_construct>("Method_site_Returns_site_type"sv),
  concepts::convertible_to<method_image, image_type_construct>("Method_image_Returns_image_type"sv));

} // namespace pixel_concept_traits

inline constexpr auto Pixel =
  concepts::make_concept_map(pixel_concept_traits::PixelConstructs, pixel_concept_traits::PointType_Is_SiteType,
                             pixel_concept_traits::ValueType_IsNotA_Reference, pixel_concept_traits::HasMethods);


template <>
struct metaprog::concepts::diagnostic::traits<std::decay_t<decltype(Pixel)>> {
  template <typename PixelType>
  static constexpr void diagnose()
  {
    static_assert(Pixel.check_at<PixelType>("PixelConstructs"sv), "PixelConstructs attribute missing");

    static_assert(Pixel.check_at<PixelType>("PointType_Is_SiteType"sv), "point_type should alias site_type");
    static_assert(Pixel.check_at<PixelType>("ValueType_IsNotA_Reference"sv), "value_type should not be a reference");

    static_assert(Pixel.check_at<PixelType>("HasMethods"sv), "methods missing or ill-defined");
    static_assert(Pixel.check_at<PixelType>("Method_val_Returns_reference"sv), "method val's return type is wrong");
    static_assert(Pixel.check_at<PixelType>("Method_point_Returns_point"sv), "method point's return type is wrong");
    static_assert(Pixel.check_at<PixelType>("Method_site_Returns_site_type"sv), "method site's return type is wrong");
    static_assert(Pixel.check_at<PixelType>("Method_image_Returns_image_type"sv),
                  "method image's return type is wrong");
  }
};

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
static_assert(!Pixel.check<MyBadPixel>(), "MyBadPixel models the Pixel concept!");

int main()
{
  if constexpr (!Pixel.check<MyPixel>()) {
    Pixel.diagnostic<MyPixel>();
  }
  /*
  if constexpr (!Pixel.check<MyBadPixel>()) {
    Pixel.diagnostic<MyBadPixel>();
  }
  */
  return 0;
}
