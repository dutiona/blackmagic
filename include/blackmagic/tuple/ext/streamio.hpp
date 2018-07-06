#pragma once

#include "print_all.hpp"

#include <ostream>
#include <tuple>

template <typename... Ts>
std::ostream& operator<<(std::ostream& os, const std::tuple<Ts...>& tpl)
{
  blackmagic::tuple::print_all(tpl, os);
  return os;
}
