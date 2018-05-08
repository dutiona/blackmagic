#include <blackmagic/concepts/concepts.hpp>

#include <string_view>

using namespace std::literals;
namespace concepts = metaprog::concepts;

struct default_constructible_test {
};
struct not_default_constructible_test {
  not_default_constructible_test() = delete;
};

constexpr auto cpt_map = concepts::make_concept_map(concepts::DefaultConstructible, concepts::Destructible);

constexpr bool f()
{
  cpt_map.require<default_constructible_test>();
  cpt_map.require_at<default_constructible_test>("DefaultConstructible"sv);
  return true;
}

static_assert(f());
static_assert(cpt_map.check<default_constructible_test>());
static_assert(cpt_map.check_at<default_constructible_test>("Destructible"sv));

int main()
{
  return 0;
}
