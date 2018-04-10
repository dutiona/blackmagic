#include <metaprog/type/type.hpp>

namespace type = metaprog::type;

using my_list_factory = type::type_list_factory<int, bool, double, char, long long, unsigned>;

static_assert(type::list_size<my_list_factory> == 6, "");
static_assert(std::is_same_v<type::list_head<my_list_factory>::type, int>, "");
static_assert(type::elem_index<type::list_head<my_list_factory>> == 0, "");
static_assert(std::is_same_v<type::next_head_t<type::list<my_list_factory>>, bool>, "");
static_assert(type::next_head_index<type::list<my_list_factory>> == 1, "");


using current0_at3 = type::call_t<type::list_at<my_list_factory>, type::size_t_<3>>;
static_assert(std::is_same_v<type::head_t<current0_at3>, char>, "");
using current2     = type::tail<type::list_tail<my_list_factory>>;
using current2_at2 = type::call_t<type::at<current2>, type::size_t_<2>>;
static_assert(std::is_same_v<type::head_t<current2_at2>, double>, "");

using current2_end = type::call_t<type::end<current2>>;
static_assert(current2_end::tail_size == 0, "");
static_assert(current2_end::list_size == 6, "");
static_assert(type::head<current2_end>{}
                == type::head<type::call_t<type::list_at<my_list_factory>, type::size_t_<6>>>{},
              "");


using my_tiny_list_factory = type::type_list_factory<char>;
static_assert(type::list_size<my_tiny_list_factory> == 1, "");
static_assert(std::is_same_v<type::list_head<my_tiny_list_factory>::type, char>, "");
static_assert(type::elem_index<type::list_head<my_tiny_list_factory>> == 0, "");
static_assert(type::next_head<type::list<my_tiny_list_factory>>{}
                == type::head<type::call_t<type::list_end<my_tiny_list_factory>>>{},
              "");

using my_empty_list_factory = type::type_list_factory<>;
static_assert(type::list_size<my_list_factory> == 6, "");
static_assert(std::is_same_v<type::list_head<my_list_factory>::type, int>, "");
static_assert(type::elem_index<type::list_head<my_list_factory>> == 0, "");
static_assert(std::is_same_v<type::next_head_t<type::list<my_list_factory>>, bool>, "");
static_assert(type::next_head_index<type::list<my_list_factory>> == 1, "");

using case_is_double = type::helpers::make_both_from_trait<std::is_same, double>;

template <typename T>
using test_switch = type::switch_<T, type::case_<case_is_double, std::true_type>, type::default_<std::false_type>>;

static_assert(std::is_same_v<std::true_type, type::call_t<test_switch<double>>>, "");
static_assert(std::is_same_v<std::false_type, type::call_t<test_switch<int>>>, "");

int main()
{
  return 0;
}
