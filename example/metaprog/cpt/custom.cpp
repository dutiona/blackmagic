#include <metaprog/cpt/cpt.hpp>

#include <string_view>

struct default_constructible_test {
};
struct not_default_constructible_test {
  not_default_constructible_test() = delete;
};

namespace concepts = cpt::concepts;
using namespace std::literals;

int main()
{
  using namespace std::literals;
  constexpr auto cpt_map   = cpt::make_concept_map(concepts::default_constructible, concepts::destructible);
  cpt::require_map<default_constructible_test>(cpt_map);
  cpt::require_map_at<default_constructible_test>(cpt_map, "test1"sv);
  [[maybe_unused]] constexpr bool ret  = cpt::check_map<default_constructible_test>(cpt_map);
  [[maybe_unused]] constexpr bool ret2 = cpt::check_map_at<default_constructible_test>(cpt_map, "test2"sv);
  return 0;
}
