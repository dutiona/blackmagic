#pragma once

#ifndef CTX_PAIR_HPP_
#define CTX_PAIR_HPP_

namespace ctx {

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

} // namespace ctx

#endif // CTX_PAIR_HPP_
