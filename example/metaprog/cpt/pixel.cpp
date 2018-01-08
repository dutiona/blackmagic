#include <metaprog/cpt/cpt.hpp>

using namespace std::literals;


namespace pixel_concept_traits {

template <typename PixelType>
using value_type_construct             = typename PixelType::value_type;
using value_type_concept               = cpt::make_custom_concept_from_construct<value_type_construct>;
constexpr auto value_type_concept_item = cpt::make_concept_item<value_type_concept>("value_type_concept"sv);

template <typename PixelType>
using reference_construct             = typename PixelType::reference;
using reference_concept               = cpt::make_custom_concept_from_construct<reference_construct>;
constexpr auto reference_concept_item = cpt::make_concept_item<reference_concept>("reference_concept"sv);

template <typename PixelType>
using point_type_construct             = typename PixelType::point_type;
using point_type_concept               = cpt::make_custom_concept_from_construct<point_type_construct>;
constexpr auto point_type_concept_item = cpt::make_concept_item<point_type_concept>("point_type_concept"sv);

template <typename PixelType>
using site_type_construct             = typename PixelType::site_type;
using site_type_concept               = cpt::make_custom_concept_from_construct<site_type_construct>;
constexpr auto site_type_concept_item = cpt::make_concept_item<site_type_concept>("site_type_concept"sv);

template <typename PixelType>
using image_type_construct             = typename PixelType::image_type;
using image_type_concept               = cpt::make_custom_concept_from_construct<image_type_construct>;
constexpr auto image_type_concept_item = cpt::make_concept_item<image_type_concept>("image_type_concept"sv);

// point_type alias site_type
template <typename PixelType>
using point_type_is_site_type_predicate = cpt::make_predicate<
  cpt::make_condition<cpt::check<point_type_concept, PixelType>()>,
  cpt::make_condition<cpt::check<site_type_concept, PixelType>()>,
  cpt::make_condition<std::is_same_v<site_type_construct<PixelType>, point_type_construct<PixelType>>>>;
using point_type_is_site_type_predicate_concept =
  cpt::make_custom_concept_from_predicate<point_type_is_site_type_predicate>;
constexpr auto point_type_is_site_type_predicate_concept_item =
  cpt::make_concept_item<point_type_is_site_type_predicate_concept>("point_type_is_site_type_predicate_concept"sv);

// value type is not reference
template <typename PixelType>
using value_type_is_not_a_reference_predicate = cpt::make_predicate<
  cpt::make_condition<cpt::check<value_type_concept, PixelType>()>>,
  cpt::make_condition<!std::is_reference_v<value_type_construct<PixelType>>>
  >;
using value_type_is_not_a_reference_predicate_concept =
cpt::make_custom_concept_from_predicate<value_type_is_not_a_reference_predicate>;
constexpr auto value_type_is_not_a_reference_predicate_concept_item =
  cpt::make_concept_item<value_type_is_not_a_reference_predicate_concept>("value_type_is_not_a_reference_predicate_concept"sv);

// has method val
template <typename PixelType>
using has_method_val_predicate =
  cpt::make_predicate<cpt::make_condition<cpt::check<reference_concept, PixelType>()>,
                      cpt::make_condition<cpt::check<cpt::concepts::invocable_r, typename PixelType::reference,
                                                     decltype(&PixelType::val), PixelType>()>>> ;
using has_method_val_predicate_concept = cpt::make_custom_concept_from_predicate<has_method_val_predicate>;
constexpr auto has_method_val_predicate_concept_item =
  cpt::make_concept_item<cpt::make_custom_concept_from_predicate<has_method_val_predicate_concept>>(
    "has_method_val_predicate_concept"sv);

// has method point
template <typename PixelType>
using has_method_point_predicate =
  cpt::make_predicate<cpt::make_condition<cpt::check<point_type_concept, PixelType>()>,
                      cpt::make_condition<cpt::check<cpt::concepts::invocable_r, typename PixelType::point_type,
                                                     decltype(&PixelType::point), PixelType>()>>> ;
using has_method_point_predicate_concept = cpt::make_custom_concept_from_predicate<has_method_point_predicate>;
constexpr auto has_method_point_predicate_concept_item =
  cpt::make_concept_item<cpt::make_custom_concept_from_predicate<has_method_point_predicate_concept>>(
    "has_method_point_predicate_concept"sv);

site_type (Pix::*method3)() const   = &Pix::site;
image_type& (Pix::*method4)() const = &Pix::image;

(void) method1;
(void) method2;
(void) method3;
(void) method4;


// value_type should not be a reference



} // namespace pixel_concept_traits

constexpr auto pixel_concept =
  cpt::make_concept_map(pixel_concept_traits::value_type_concept_item, pixel_concept_traits::getV_concept_item);

struct MyPixel {
  using value_type = void;
  value_type getV();
};

struct MyBadPixel {
  using ValueType = void;
};

static_assert(cpt::check_map<MyPixel>(pixel_concept), "Check concept map for MyPixel");
static_assert(!cpt::check_map<MyBadPixel>(pixel_concept), "Check concept map for MyBadPixel");

int main()
{
  return 0;
}
