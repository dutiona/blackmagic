#include <metaprog/cpt/cpt.hpp>

using namespace std::literals;


namespace pixel_concept_traits {

template <typename PixelType>
using value_type_construct = typename PixelType::value_type;
constexpr auto value_type_concept =
  cpt::make_custom_concept_item_from_construct<value_type_construct>("value_type_concept"sv);

template <typename PixelType>
using reference_construct = typename PixelType::reference;
constexpr auto reference_concept =
  cpt::make_custom_concept_item_from_construct<reference_construct>("reference_concept"sv);

template <typename PixelType>
using point_type_construct = typename PixelType::point_type;
constexpr auto point_type_concept =
  cpt::make_custom_concept_item_from_construct<point_type_construct>("point_type_concept"sv);

template <typename PixelType>
using site_type_construct = typename PixelType::site_type;
constexpr auto site_type_concept =
  cpt::make_custom_concept_item_from_construct<site_type_construct>("site_type_concept"sv);

template <typename PixelType>
using image_type_construct = typename PixelType::image_type;
constexpr auto image_type_concept =
  cpt::make_custom_concept_item_from_construct<image_type_construct>("image_type_concept"sv);

// point_type alias site_type
template <typename PixelType>
using point_type_is_site_type_predicate = cpt::make_predicate<
  cpt::make_condition<cpt::check<PixelType>(point_type_concept)>,
  cpt::make_condition<cpt::check<PixelType>(site_type_concept)>,
  cpt::make_condition<std::is_same_v<site_type_construct<PixelType>, point_type_construct<PixelType>>>>;
constexpr auto point_type_is_site_type_predicate_concept =
  cpt::make_custom_concept_item_from_predicate<point_type_is_site_type_predicate>(
    "point_type_is_site_type_predicate_concept"sv);

// value type is not reference
template <typename PixelType>
using value_type_is_not_a_reference_predicate =
  cpt::make_predicate<cpt::make_condition<cpt::check<PixelType>(value_type_concept)>,
                      cpt::make_condition<!std::is_reference_v<value_type_construct<PixelType>>>>;
constexpr auto value_type_is_not_a_reference_predicate_concept =
  cpt::make_custom_concept_item_from_predicate<value_type_is_not_a_reference_predicate>(
    "value_type_is_not_a_reference_predicate_concept"sv);

// has method val
template <typename PixelType>
using has_method_val_predicate =
  cpt::make_predicate<cpt::make_condition<cpt::check<PixelType>(reference_concept)>,
                      cpt::make_condition<cpt::check<cpt::concepts::invocable_r, reference_construct<PixelType>,
                                                     decltype(&PixelType::val), PixelType>()>>;
constexpr auto has_method_val_predicate_concept =
  cpt::make_custom_concept_item_from_predicate<has_method_val_predicate>("has_method_val_predicate_concept"sv);

// has method point
template <typename PixelType>
using has_method_point_predicate =
  cpt::make_predicate<cpt::make_condition<cpt::check<PixelType>(point_type_concept)>,
                      cpt::make_condition<cpt::check<cpt::concepts::invocable_r, point_type_construct<PixelType>,
                                                     decltype(&PixelType::point), PixelType>()>>;
constexpr auto has_method_point_predicate_concept =
  cpt::make_custom_concept_item_from_predicate<has_method_point_predicate>("has_method_point_predicate_concept"sv);

// has method site
template <typename PixelType>
using has_method_site_predicate =
  cpt::make_predicate<cpt::make_condition<cpt::check<PixelType>(site_type_concept)>,
                      cpt::make_condition<cpt::check<cpt::concepts::invocable_r, site_type_construct<PixelType>,
                                                     decltype(&PixelType::site), PixelType>()>>;
constexpr auto has_method_site_predicate_concept =
  cpt::make_custom_concept_item_from_predicate<has_method_site_predicate>("has_method_site_predicate_concept"sv);

// has method image
template <typename PixelType>
using has_method_image_predicate =
  cpt::make_predicate<cpt::make_condition<cpt::check<PixelType>(image_type_concept)>,
                      cpt::make_condition<cpt::check<cpt::concepts::invocable_r, image_type_construct<PixelType>,
                                                     decltype(&PixelType::image), PixelType>()>>;
constexpr auto has_method_image_predicate_concept =
  cpt::make_custom_concept_item_from_predicate<has_method_image_predicate>("has_method_image_predicate_concept"sv);


} // namespace pixel_concept_traits

constexpr auto pixel_concept = cpt::make_concept_map(
  pixel_concept_traits::value_type_concept, pixel_concept_traits::reference_concept,
  pixel_concept_traits::point_type_concept, pixel_concept_traits::site_type_concept,
  pixel_concept_traits::image_type_concept, pixel_concept_traits::point_type_is_site_type_predicate_concept,
  pixel_concept_traits::value_type_is_not_a_reference_predicate_concept,
  pixel_concept_traits::has_method_val_predicate_concept, pixel_concept_traits::has_method_point_predicate_concept,
  pixel_concept_traits::has_method_site_predicate_concept, pixel_concept_traits::has_method_image_predicate_concept);

namespace concept_diagnostic_traits {

template <typename PixelType>
constexpr void diagnostic(decltype(pixel_concept))
{
  static_assert(cpt::check<PixelType>(pixel_concept_traits::value_type_concept), "value_type_concept");
  static_assert(cpt::check<PixelType>(pixel_concept_traits::reference_concept), "reference_concept");
  static_assert(cpt::check<PixelType>(pixel_concept_traits::point_type_concept), "point_type_concept");
  static_assert(cpt::check<PixelType>(pixel_concept_traits::site_type_concept), "site_type_concept");
  static_assert(cpt::check<PixelType>(pixel_concept_traits::image_type_concept), "image_type_concept");

  static_assert(cpt::check<PixelType>(pixel_concept_traits::point_type_is_site_type_predicate_concept),
                "point_type_is_site_type_predicate_concept");
  static_assert(cpt::check<PixelType>(pixel_concept_traits::value_type_is_not_a_reference_predicate_concept),
                "value_type_is_not_a_reference_predicate_concept");

  static_assert(cpt::check<PixelType>(pixel_concept_traits::has_method_val_predicate_concept),
                "has_method_val_predicate_concept");
  static_assert(cpt::check<PixelType>(pixel_concept_traits::has_method_point_predicate_concept),
                "has_method_point_predicate_concept");
  static_assert(cpt::check<PixelType>(pixel_concept_traits::has_method_site_predicate_concept),
                "has_method_site_predicate_concept");
  static_assert(cpt::check<PixelType>(pixel_concept_traits::has_method_image_predicate_concept),
                "has_method_image_predicate_concept");
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
    // DIAGNOSTIC(pixel_concept, MyBadPixel);
  }

  return 0;
}
