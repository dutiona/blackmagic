#include <metaprog/cpt/cpt.hpp>

using namespace std::literals;
namespace concepts = cpt::concepts;

namespace pixel_concept_traits {

template <typename PixelType>
using value_type_construct       = typename PixelType::value_type;
inline constexpr auto ValueType = cpt::make_concept_item_from_construct<value_type_construct>("ValueType"sv);

template <typename PixelType>
using reference_construct       = typename PixelType::reference;
inline constexpr auto Reference = cpt::make_concept_item_from_construct<reference_construct>("Reference"sv);

template <typename PixelType>
using point_type_construct       = typename PixelType::point_type;
inline constexpr auto PointType = cpt::make_concept_item_from_construct<point_type_construct>("PointType"sv);

template <typename PixelType>
using site_type_construct       = typename PixelType::site_type;
inline constexpr auto SiteType = cpt::make_concept_item_from_construct<site_type_construct>("SiteType"sv);

template <typename PixelType>
using image_type_construct       = typename PixelType::image_type;
inline constexpr auto ImageType = cpt::make_concept_item_from_construct<image_type_construct>("ImageType"sv);

// point_type alias site_type
template <typename PixelType>
using point_type_is_site_type_predicate = cpt::make_predicate<
  cpt::make_condition<PointType.check<PixelType>()>, cpt::make_condition<SiteType.check<PixelType>()>,
  cpt::make_condition<std::is_same_v<site_type_construct<PixelType>, point_type_construct<PixelType>>>>;
inline constexpr auto PointType_Is_SiteType =
  cpt::make_concept_item_from_predicate<point_type_is_site_type_predicate>("PointType_Is_SiteType"sv);

// value type is not reference
template <typename PixelType>
using value_type_is_not_a_reference_predicate =
  cpt::make_predicate<cpt::make_condition<ValueType.check<PixelType>()>,
                      cpt::make_condition<!std::is_reference_v<value_type_construct<PixelType>>>>;
inline constexpr auto ValueType_IsNot_Reference =
  cpt::make_concept_item_from_predicate<value_type_is_not_a_reference_predicate>("ValueType_IsNot_Reference"sv);

// has method val
template <typename PixelType>
using has_method_val_predicate =
  cpt::make_predicate<cpt::make_condition<Reference.check<PixelType>()>,
                      cpt::make_condition<concepts::InvocableR.check<reference_construct<PixelType>,
                                                                      decltype(&PixelType::val), PixelType>()>>;
constexpr auto HasMethod_Val = cpt::make_concept_item_from_predicate<has_method_val_predicate>("HasMethod_Val"sv);

// has method point
template <typename PixelType>
using has_method_point_predicate =
  cpt::make_predicate<cpt::make_condition<PointType.check<PixelType>()>,
                      cpt::make_condition<concepts::InvocableR.check<point_type_construct<PixelType>,
                                                                      decltype(&PixelType::point), PixelType>()>>;
constexpr auto HasMethod_Point =
  cpt::make_concept_item_from_predicate<has_method_point_predicate>("HasMethod_Point"sv);

// has method site
template <typename PixelType>
using has_method_site_predicate =
  cpt::make_predicate<cpt::make_condition<SiteType.check<PixelType>()>,
                      cpt::make_condition<concepts::InvocableR.check<site_type_construct<PixelType>,
                                                                      decltype(&PixelType::site), PixelType>()>>;
constexpr auto HasMethod_Site = cpt::make_concept_item_from_predicate<has_method_site_predicate>("HasMethod_Site"sv);

// has method image
template <typename PixelType>
using has_method_image_predicate =
  cpt::make_predicate<cpt::make_condition<ImageType.check<PixelType>()>,
                      cpt::make_condition<concepts::InvocableR.check<image_type_construct<PixelType>,
                                                                      decltype(&PixelType::image), PixelType>()>>;
constexpr auto HasMethod_Image =
  cpt::make_concept_item_from_predicate<has_method_image_predicate>("HasMethod_Image"sv);


} // namespace pixel_concept_traits

constexpr auto pixel_concept = cpt::make_concept_map(
  pixel_concept_traits::ValueType, pixel_concept_traits::Reference, pixel_concept_traits::PointType,
  pixel_concept_traits::SiteType, pixel_concept_traits::ImageType, pixel_concept_traits::PointType_Is_SiteType,
  pixel_concept_traits::ValueType_IsNot_Reference, pixel_concept_traits::HasMethod_Val,
  pixel_concept_traits::HasMethod_Point, pixel_concept_traits::HasMethod_Site,
  pixel_concept_traits::HasMethod_Image);

namespace concept_diagnostic_traits {

template <typename PixelType>
constexpr void diagnostic(decltype(pixel_concept))
{
  static_assert(pixel_concept.check_at<PixelType>("ValueType"sv), "value_type attribute missing");
  static_assert(pixel_concept.check_at<PixelType>("Reference"sv), "reference attribute missing");
  static_assert(pixel_concept.check_at<PixelType>("PointType"sv), "point_type attribute missing");
  static_assert(pixel_concept.check_at<PixelType>("SiteType"sv), "site_type attribute missing");
  static_assert(pixel_concept.check_at<PixelType>("ImageType"sv), "image_type attribute missing");

  static_assert(pixel_concept.check_at<PixelType>("PointType_Is_SiteType"sv), "point_type should alias site_type");
  static_assert(pixel_concept.check_at<PixelType>("ValueType_IsNot_Reference"sv),
                "value_type should not be a reference");

  static_assert(pixel_concept.check_at<PixelType>("HasMethod_Val"sv), "method val missing or ill-defined");
  static_assert(pixel_concept.check_at<PixelType>("HasMethod_Point"sv), "method point missing or ill-defined");
  static_assert(pixel_concept.check_at<PixelType>("HasMethod_Site"sv), "method site missing or ill-defined");
  static_assert(pixel_concept.check_at<PixelType>("HasMethod_Image"sv), "method image missing or ill-defined");
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


int main()
{
  if constexpr (!pixel_concept.check<MyPixel>()) {
    DIAGNOSTIC(pixel_concept, MyPixel);
  }
  if constexpr (!pixel_concept.check<MyBadPixel>()) {
    // DIAGNOSTIC(pixel_concept, MyBadPixel);
  }

  return 0;
}
