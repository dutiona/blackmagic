#include <metaprog/cpt/cpt.hpp>

using namespace std::literals;


namespace pixel_concept_traits {

template <typename PixelType>
using has_value_type = typename PixelType::value_type;
using has_value_type_concept = cpt::make_custom_concept_from_construct<has_value_type>;
constexpr auto value_type_concept_item =
  cpt::make_concept_item<has_value_type_concept>("value_type_concept"sv);

template<typename PixelType>
using has_getV_predicate = cpt::make_predicate<
  cpt::make_condition<cpt::check<has_value_type_concept, PixelType>()>,
  cpt::make_condition<cpt::check<cpt::concepts::invocable_r, typename PixelType::value_type, decltype(&PixelType::getV), PixelType>()>
>;

constexpr auto getV_concept_item =
  cpt::make_concept_item<cpt::make_custom_concept_from_predicate<has_getV_predicate>>("has_getV_concept"sv);

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
