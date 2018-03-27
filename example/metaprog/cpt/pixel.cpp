#include <metaprog/concepts/concepts.hpp>

#include <string_view>

using namespace std::literals;
namespace concepts = metaprog::concepts;

namespace pixel_concept_traits {

template <typename PixelType>
using value_type_construct      = typename PixelType::value_type;
inline constexpr auto ValueType = concepts::make_concept_item_from_construct<value_type_construct>("ValueType"sv);

template <typename PixelType>
using reference_construct       = typename PixelType::reference;
inline constexpr auto Reference = concepts::make_concept_item_from_construct<reference_construct>("Reference"sv);

template <typename PixelType>
using point_type_construct      = typename PixelType::point_type;
inline constexpr auto PointType = concepts::make_concept_item_from_construct<point_type_construct>("PointType"sv);

template <typename PixelType>
using site_type_construct      = typename PixelType::site_type;
inline constexpr auto SiteType = concepts::make_concept_item_from_construct<site_type_construct>("SiteType"sv);

template <typename PixelType>
using image_type_construct      = typename PixelType::image_type;
inline constexpr auto ImageType = concepts::make_concept_item_from_construct<image_type_construct>("ImageType"sv);

// point_type alias site_type
template <typename PixelType>
using point_type_is_site_type_predicate = concepts::make_predicate<
  concepts::make_condition<PointType.check<PixelType>()>, concepts::make_condition<SiteType.check<PixelType>()>,
  concepts::make_condition<std::is_same_v<site_type_construct<PixelType>, point_type_construct<PixelType>>>>;
inline constexpr auto PointType_Is_SiteType =
  concepts::make_concept_item_from_predicate<point_type_is_site_type_predicate>("PointType_Is_SiteType"sv);

// value type is not reference
template <typename PixelType>
using value_type_is_not_a_reference_predicate =
  concepts::make_predicate<concepts::make_condition<ValueType.check<PixelType>()>,
                           concepts::make_condition<!std::is_reference_v<value_type_construct<PixelType>>>>;
inline constexpr auto ValueType_IsNot_Reference =
  concepts::make_concept_item_from_predicate<value_type_is_not_a_reference_predicate>("ValueType_IsNot_Reference"sv);

// has method val
template <typename PixelType>
using has_method_val_predicate =
  concepts::make_predicate<concepts::make_condition<Reference.check<PixelType>()>,
                           concepts::make_condition<concepts::InvocableR.check<
                             reference_construct<PixelType>, decltype(&PixelType::val), PixelType>()>>;
inline constexpr auto HasMethod_Val =
  concepts::make_concept_item_from_predicate<has_method_val_predicate>("HasMethod_Val"sv);

// has method point
template <typename PixelType>
using has_method_point_predicate =
  concepts::make_predicate<concepts::make_condition<PointType.check<PixelType>()>,
                           concepts::make_condition<concepts::InvocableR.check<
                             point_type_construct<PixelType>, decltype(&PixelType::point), PixelType>()>>;
inline constexpr auto HasMethod_Point =
  concepts::make_concept_item_from_predicate<has_method_point_predicate>("HasMethod_Point"sv);

// has method site
template <typename PixelType>
using has_method_site_predicate =
  concepts::make_predicate<concepts::make_condition<SiteType.check<PixelType>()>,
                           concepts::make_condition<concepts::InvocableR.check<
                             site_type_construct<PixelType>, decltype(&PixelType::site), PixelType>()>>;
inline constexpr auto HasMethod_Site =
  concepts::make_concept_item_from_predicate<has_method_site_predicate>("HasMethod_Site"sv);

// has method image
template <typename PixelType>
using has_method_image_predicate =
  concepts::make_predicate<concepts::make_condition<ImageType.check<PixelType>()>,
                           concepts::make_condition<concepts::InvocableR.check<
                             image_type_construct<PixelType>, decltype(&PixelType::image), PixelType>()>>;
inline constexpr auto HasMethod_Image =
  concepts::make_concept_item_from_predicate<has_method_image_predicate>("HasMethod_Image"sv);


} // namespace pixel_concept_traits

inline constexpr auto Pixel = concepts::make_concept_map(
  pixel_concept_traits::ValueType, pixel_concept_traits::Reference, pixel_concept_traits::PointType,
  pixel_concept_traits::SiteType, pixel_concept_traits::ImageType, pixel_concept_traits::PointType_Is_SiteType,
  pixel_concept_traits::ValueType_IsNot_Reference, pixel_concept_traits::HasMethod_Val,
  pixel_concept_traits::HasMethod_Point, pixel_concept_traits::HasMethod_Site, pixel_concept_traits::HasMethod_Image);

namespace concept_diagnostic_traits {

template <typename PixelType>
constexpr void diagnostic(decltype(Pixel))
{
  static_assert(Pixel.check_at<PixelType>("ValueType"sv), "value_type attribute missing");
  static_assert(Pixel.check_at<PixelType>("Reference"sv), "reference attribute missing");
  static_assert(Pixel.check_at<PixelType>("PointType"sv), "point_type attribute missing");
  static_assert(Pixel.check_at<PixelType>("SiteType"sv), "site_type attribute missing");
  static_assert(Pixel.check_at<PixelType>("ImageType"sv), "image_type attribute missing");

  static_assert(Pixel.check_at<PixelType>("PointType_Is_SiteType"sv), "point_type should alias site_type");
  static_assert(Pixel.check_at<PixelType>("ValueType_IsNot_Reference"sv), "value_type should not be a reference");

  static_assert(Pixel.check_at<PixelType>("HasMethod_Val"sv), "method val missing or ill-defined");
  static_assert(Pixel.check_at<PixelType>("HasMethod_Point"sv), "method point missing or ill-defined");
  static_assert(Pixel.check_at<PixelType>("HasMethod_Site"sv), "method site missing or ill-defined");
  static_assert(Pixel.check_at<PixelType>("HasMethod_Image"sv), "method image missing or ill-defined");
}

} // namespace concept_diagnostic_traits


struct MyPixel {
  using value_type = int;
  using reference  = int&;
  using point_type = double;
  using site_type  = double;
  using image_type = void;

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
  using image_type = void;

  reference  val();
  point_type point();
  site_type  site();
  image_type image();
};

// Vérification
static_assert(Pixel.check<MyPixel>(), "MyPixel doesn't model the Pixel concept!");

int main()
{
  if constexpr (!Pixel.check<MyPixel>()) {
    DIAGNOSTIC(Pixel, MyPixel);
  }
  if constexpr (!Pixel.check<MyBadPixel>()) {
    // DIAGNOSTIC(Pixel, MyBadPixel);
  }

  return 0;
}
