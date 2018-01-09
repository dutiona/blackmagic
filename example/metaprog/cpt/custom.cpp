#include <metaprog/cpt/cpt.hpp>

#include <string_view>

using namespace std::literals;
namespace concepts = cpt::concepts;

struct default_constructible_test {
};
struct not_default_constructible_test {
  not_default_constructible_test() = delete;
};

constexpr auto cpt_map = cpt::make_concept_map(concepts::default_constructible, concepts::destructible);

constexpr bool f() {
  cpt::require_map<default_constructible_test>(cpt_map);
  cpt::require_map_at<default_constructible_test>(cpt_map, "test1"sv);
  return true;
}

static_assert(f(), "");
static_assert(cpt::check_map<default_constructible_test>(cpt_map), "");
static_assert(cpt::check_map_at<default_constructible_test>(cpt_map, "test2"sv), "");

int main()
{
  return 0;
}
