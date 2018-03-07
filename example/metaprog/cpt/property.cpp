#include <metaprog/type/type.hpp>

namespace list     = type::list;
namespace algo     = type::algorithm;
namespace literals = type::literals;

using my_list_factory = list::type_list_factory<int, bool, double, char, long long, unsigned>;

static_assert(list::list_size<my_list_factory> == 6, "");
static_assert(std::is_same_v<list::list_head<my_list_factory>::type, int>, "");
static_assert(list::elem_index<list::list_head<my_list_factory>> == 0, "");
static_assert(std::is_same_v<list::next_head_t<list::list<my_list_factory>>, bool>, "");
static_assert(list::next_head_index<list::list<my_list_factory>> == 1, "");


using current0_at3 = algo::call_t<algo::list_at<my_list_factory>, literals::size_t_<3>>;
static_assert(std::is_same_v<list::head_t<current0_at3>, char>, "");
using current2     = list::tail<list::list_tail<my_list_factory>>;
using current2_at2 = algo::call_t<algo::at<current2>, literals::size_t_<2>>;
static_assert(std::is_same_v<list::head_t<current2_at2>, double>, "");

using current2_end = algo::call_t<algo::end<current2>>;
static_assert(current2_end::tail_size == 0, "");
static_assert(current2_end::list_size == 6, "");
static_assert(list::head<current2_end>{}
                == list::head<algo::call_t<algo::list_at<my_list_factory>, literals::size_t_<6>>>{},
              "");


using my_tiny_list_factory = list::type_list_factory<char>;
static_assert(list::list_size<my_tiny_list_factory> == 1, "");
static_assert(std::is_same_v<list::list_head<my_tiny_list_factory>::type, char>, "");
static_assert(list::elem_index<list::list_head<my_tiny_list_factory>> == 0, "");
static_assert(list::next_head<list::list<my_tiny_list_factory>>{}
                == list::head<algo::call_t<algo::list_end<my_tiny_list_factory>>>{},
              "");

using my_empty_list_factory = list::type_list_factory<>;
static_assert(list::list_size<my_list_factory> == 6, "");
static_assert(std::is_same_v<list::list_head<my_list_factory>::type, int>, "");
static_assert(list::elem_index<list::list_head<my_list_factory>> == 0, "");
static_assert(std::is_same_v<list::next_head_t<list::list<my_list_factory>>, bool>, "");
static_assert(list::next_head_index<list::list<my_list_factory>> == 1, "");

struct case_is_double {
  template <typename T>
  static constexpr bool value = std::is_same_v<T, double>;
};

template <typename T>
using test_switch = algo::switch_<T, algo::case_<case_is_double, std::true_type>, algo::default_<std::false_type>>;

static_assert(std::is_same_v<std::true_type, algo::call_t<test_switch<double>>>, "");
static_assert(std::is_same_v<std::false_type, algo::call_t<test_switch<int>>>, "");

int main()
{
  return 0;
}
