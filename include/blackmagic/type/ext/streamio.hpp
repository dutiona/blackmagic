#pragma once

#include "../list.hpp"
#include "print.hpp"

#include <ostream>

template <typename... Ts>
std::ostream& operator<<(std::ostream& os, const blackmagic::type::type_list<Ts...>&)
{
  blackmagic::type::print<blackmagic::type::type_list<Ts...>>(os);
  return os;
}
