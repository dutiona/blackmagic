#include <metaprog/cpt/cpt.hpp>

using namespace std::literals;


namespace pixel_concept_traits {

template <typename PixelType>
using value_type_construct       = typename PixelType::value_type;
inline constexpr auto value_type = cpt::make_concept_item_from_construct<value_type_construct>("value_type"sv);

template <typename PixelType>
using reference_construct       = typename PixelType::reference;
inline constexpr auto reference = cpt::make_concept_item_from_construct<reference_construct>("reference"sv);

template <typename PixelType>
using point_type_construct       = typename PixelType::point_type;
inline constexpr auto point_type = cpt::make_concept_item_from_construct<point_type_construct>("point_type"sv);

template <typename PixelType>
using site_type_construct       = typename PixelType::site_type;
inline constexpr auto site_type = cpt::make_concept_item_from_construct<site_type_construct>("site_type"sv);

template <typename PixelType>
using image_type_construct       = typename PixelType::image_type;
inline constexpr auto image_type = cpt::make_concept_item_from_construct<image_type_construct>("image_type"sv);

// point_type alias site_type
template <typename PixelType>
using point_type_is_site_type_predicate = cpt::make_predicate<
  cpt::make_condition<cpt::check<PixelType>(point_type)>, cpt::make_condition<cpt::check<PixelType>(site_type)>,
  cpt::make_condition<std::is_same_v<site_type_construct<PixelType>, point_type_construct<PixelType>>>>;
inline constexpr auto point_type_is_site_type =
  cpt::make_concept_item_from_predicate<point_type_is_site_type_predicate>("point_type_is_site_type"sv);

// value type is not reference
template <typename PixelType>
using value_type_is_not_a_reference_predicate =
  cpt::make_predicate<cpt::make_condition<cpt::check<PixelType>(value_type)>,
                      cpt::make_condition<!std::is_reference_v<value_type_construct<PixelType>>>>;
inline constexpr auto value_type_is_not_a_reference =
  cpt::make_concept_item_from_predicate<value_type_is_not_a_reference_predicate>("value_type_is_not_a_reference"sv);

// has method val
template <typename PixelType>
using has_method_val_predicate =
  cpt::make_predicate<cpt::make_condition<cpt::check<PixelType>(reference)>,
                      cpt::make_condition<cpt::check<reference_construct<PixelType>, decltype(&PixelType::val),
                                                     PixelType>(cpt::concepts::invocable_r)>>;
constexpr auto has_method_val = cpt::make_concept_item_from_predicate<has_method_val_predicate>("has_method_val"sv);

// has method point
template <typename PixelType>
using has_method_point_predicate =
  cpt::make_predicate<cpt::make_condition<cpt::check<PixelType>(point_type)>,
                      cpt::make_condition<cpt::check<point_type_construct<PixelType>, decltype(&PixelType::point),
                                                     PixelType>(cpt::concepts::invocable_r)>>;
constexpr auto has_method_point =
  cpt::make_concept_item_from_predicate<has_method_point_predicate>("has_method_point"sv);

// has method site
template <typename PixelType>
using has_method_site_predicate =
  cpt::make_predicate<cpt::make_condition<cpt::check<PixelType>(site_type)>,
                      cpt::make_condition<cpt::check<site_type_construct<PixelType>, decltype(&PixelType::site),
                                                     PixelType>(cpt::concepts::invocable_r)>>;
constexpr auto has_method_site = cpt::make_concept_item_from_predicate<has_method_site_predicate>("has_method_site"sv);

// has method image
template <typename PixelType>
using has_method_image_predicate =
  cpt::make_predicate<cpt::make_condition<cpt::check<PixelType>(image_type)>,
                      cpt::make_condition<cpt::check<image_type_construct<PixelType>, decltype(&PixelType::image),
                                                     PixelType>(cpt::concepts::invocable_r)>>;
constexpr auto has_method_image =
  cpt::make_concept_item_from_predicate<has_method_image_predicate>("has_method_image"sv);


} // namespace pixel_concept_traits

constexpr auto pixel_concept = cpt::make_concept_map(
  pixel_concept_traits::value_type, pixel_concept_traits::reference, pixel_concept_traits::point_type,
  pixel_concept_traits::site_type, pixel_concept_traits::image_type, pixel_concept_traits::point_type_is_site_type,
  pixel_concept_traits::value_type_is_not_a_reference, pixel_concept_traits::has_method_val,
  pixel_concept_traits::has_method_point, pixel_concept_traits::has_method_site,
  pixel_concept_traits::has_method_image);

namespace concept_diagnostic_traits {

template <typename PixelType>
constexpr void diagnostic(decltype(pixel_concept))
{
  static_assert(cpt::check_map_at<PixelType>(pixel_concept, "value_type"sv), "value_type attribute missing");
  static_assert(cpt::check_map_at<PixelType>(pixel_concept, "reference"sv), "reference attribute missing");
  static_assert(cpt::check_map_at<PixelType>(pixel_concept, "point_type"sv), "point_type attribute missing");
  static_assert(cpt::check_map_at<PixelType>(pixel_concept, "site_type"sv), "site_type attribute missing");
  static_assert(cpt::check_map_at<PixelType>(pixel_concept, "image_type"sv), "image_type attribute missing");

  static_assert(cpt::check_map_at<PixelType>(pixel_concept, "point_type_is_site_type"sv), "point_type should alias site_type");
  static_assert(cpt::check_map_at<PixelType>(pixel_concept, "value_type_is_not_a_reference"sv), "value_type should not be a reference");

  static_assert(cpt::check_map_at<PixelType>(pixel_concept, "has_method_val"sv), "method val missing or ill-defined");
  static_assert(cpt::check_map_at<PixelType>(pixel_concept, "has_method_point"sv), "method point missing or ill-defined");
  static_assert(cpt::check_map_at<PixelType>(pixel_concept, "has_method_site"sv), "method site missing or ill-defined");
  static_assert(cpt::check_map_at<PixelType>(pixel_concept, "has_method_image"sv), "method image missing or ill-defined");
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
  if constexpr (!cpt::check_map<MyPixel>(pixel_concept)) {
    DIAGNOSTIC(pixel_concept, MyPixel);
  }
  if constexpr (!cpt::check_map<MyBadPixel>(pixel_concept)) {
    DIAGNOSTIC(pixel_concept, MyBadPixel);
  }

  return 0;
}
