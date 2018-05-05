#if 0

#include <string_view>

using namespace std::literals;

template <typename T>
struct S {
  std::string_view s_;
  using type = T;
  constexpr S(std::string_view s)
    : s_(s)
  {
  }
};

template <typename T, typename U>
constexpr bool operator==(const S<T>& lhs, const S<U>& rhs)
{
  return lhs.s_ == rhs.s_;
}

static_assert(metaprog::tuple::front(std::make_tuple("lol"sv, 6.0)) == "lol"sv);
static_assert(metaprog::tuple::back(std::make_tuple("lol"sv, 6.0)) == 6.0, "");
static_assert(metaprog::tuple::equals(metaprog::tuple::push_front(std::make_tuple("lol"sv), 6.0),
                                      std::make_tuple(6.0, "lol"sv)));
static_assert(metaprog::tuple::equals(metaprog::tuple::push_back(std::make_tuple("lol"sv), 6.0),
                                      std::make_tuple("lol"sv, 6.0)));
static_assert(metaprog::tuple::equals(metaprog::tuple::pop_front(std::make_tuple("lol"sv, 6.0)), std::make_tuple(6.0)));
static_assert(metaprog::tuple::equals(metaprog::tuple::pop_back(std::make_tuple("lol"sv, 6.0)),
                                      std::make_tuple("lol"sv)));
static_assert(metaprog::tuple::equals(metaprog::tuple::rotate_left(std::make_tuple("lol"sv, 6.0, 4)),
                                      std::make_tuple(6.0, 4, "lol"sv)));
static_assert(metaprog::tuple::equals(metaprog::tuple::rotate_right(std::make_tuple("lol"sv, 6.0, 4)),
                                      std::make_tuple(4, "lol"sv, 6.0)));


static_assert(metaprog::tuple::equals(std::make_tuple(0, 1, 4.0, 5.0, "lol"sv),
                                      metaprog::tuple::reverse(std::make_tuple("lol"sv, 5.0, 4.0, 1, 0))));

static_assert(metaprog::tuple::fold_left(std::make_tuple(10, 2), [](auto lhs, auto rhs) { return lhs / rhs; }) == 5);

static_assert(metaprog::tuple::fold_left(std::make_tuple(2, 2, 1), [](auto lhs, auto rhs) { return lhs / rhs; }, 20)
              == 5);

static_assert(metaprog::tuple::fold_right(std::make_tuple(2, 10), [](auto lhs, auto rhs) { return lhs / rhs; }) == 5);

static_assert(metaprog::tuple::fold_right(std::make_tuple(2, 2), [](auto lhs, auto rhs) { return lhs / rhs; }, 1, 20)
              == 5);

static_assert(metaprog::tuple::unpack(std::make_tuple(1, 2, 3, 4, 5), [](auto... x) { return (x + ...); }) == 15);

inline constexpr int t[] = {1, 2, 3, 4, 5};
static_assert(metaprog::tuple::unpack(t, [](auto... x) { return (x + ...); }) == 15);

namespace common_helpers = metaprog::common::helpers;

static_assert(metaprog::tuple::equals(std::make_tuple(2.0, 48.0),
                                      metaprog::tuple::remove_if(std::make_tuple(1, 2.0, 3, 48.0, 55),
                                                                 common_helpers::trait<std::is_integral>)));
static_assert(metaprog::tuple::equals(std::make_tuple(2.0, 48.0),
                                      metaprog::tuple::remove_if(std::make_tuple(1, 2.0, 3, 48.0, 55),
                                                                 common_helpers::trait<std::is_same, int>)));

static_assert(metaprog::tuple::equals(std::make_tuple(1, 3, 55),
                                      metaprog::tuple::copy_if(std::make_tuple(1, 2.0, 3, 48.0, 55),
                                                               common_helpers::trait<std::is_integral>)));

static_assert(metaprog::tuple::equals(std::make_tuple(1, 3, 55),
                                      metaprog::tuple::copy_if(std::make_tuple(1, 2.0, 3, 48.0, 55),
                                                               common_helpers::trait<std::is_same, int>)));

static_assert(metaprog::tuple::equals(std::make_tuple(1, 2.0),
                                      metaprog::tuple::unique(std::make_tuple(1, 2.0, 3, 48.0, 55))));

#endif