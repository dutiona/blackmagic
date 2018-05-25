#pragma once

namespace blackmagic::cstxpr { inline namespace algorithm {

template <typename InputItLhs, typename InputItRhs>
constexpr bool equal(InputItLhs first_lhs, InputItLhs last_lhs, InputItRhs first_rhs, InputItRhs last_rhs)
{
  while (first_lhs != last_lhs && first_rhs != last_rhs && *first_lhs == *first_rhs) {
    ++first_lhs, ++first_rhs;
  }
  return first_lhs == last_lhs && first_rhs == last_rhs;
}

}} // namespace blackmagic::cstxpr::algorithm
