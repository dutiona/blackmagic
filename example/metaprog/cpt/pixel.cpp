#include <metaprog/cpt/cpt.hpp>

using namespace std::literals;


namespace pixel_concept_traits {

template <typename PixelType>
using has_value_type = typename PixelType::value_type;

constexpr auto value_type_concept_item =
  cpt::make_concept_item<cpt::custom_concept<has_value_type>>("value_type_concept"sv);

} // namespace pixel_concept_traits

constexpr auto pixel_concept = cpt::make_concept_map(pixel_concept_traits::value_type_concept_item);

struct MyPixel {
  using value_type = void;
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
