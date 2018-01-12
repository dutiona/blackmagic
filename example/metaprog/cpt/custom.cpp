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
  cpt_map.require<default_constructible_test>();
  cpt_map.require_at<default_constructible_test>("default_constructible"sv);
  return true;
}

static_assert(f(), "");
static_assert(cpt_map.check<default_constructible_test>(), "");
static_assert(cpt_map.check_at<default_constructible_test>("destructible"sv), "");

int main()
{
  return 0;
}
