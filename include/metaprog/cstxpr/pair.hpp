#pragma once

namespace metaprog::cstxpr {

template <typename First, typename Second>
struct pair {
  using first_type  = First;
  using second_type = Second;
  First  first;
  Second second;
};

template <typename First, typename Second>
constexpr auto make_pair(First f, Second s)
{
  return pair<First, Second>{f, s};
}

} // namespace metaprog::cstxpr
