#include <blackmagic/type/type.hpp>

namespace type = blackmagic::type;

using case_is_double = type::helpers::make_both_from_trait<std::is_same, double>;

template <typename T>
using test_switch = type::switch_<T, type::case_<case_is_double, std::true_type>, type::default_<std::false_type>>;

static_assert(std::is_same_v<std::true_type, type::call_t<test_switch<double>>>);
static_assert(std::is_same_v<std::false_type, type::call_t<test_switch<int>>>);

int main()
{
  return 0;
}
