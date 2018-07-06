#pragma once

#include "../algorithm/front.hpp"
#include "../algorithm/pop_front.hpp"

#include <ostream>
#include <typeinfo>

namespace blackmagic::type { inline namespace ext {

namespace details {
template <typename List, typename = std::enable_if_t<(List::size() == 0)>>
void print_impl(std::ostream& os)
{
  os << "<empty>";
}

template <typename List, typename = std::enable_if_t<(List::size() == 1)>>
void print_impl(std::ostream& os)
{
  os << typeid(front_t<List>).name();
}

template <typename List, typename = std::enable_if_t<(List::size() > 1)>>
void print_impl(std::ostream& os)
{
  os << typeid(front_t<List>).name() << ", ";
  print_impl<pop_front_t<List>>(os);
}

} // namespace details

template <typename List>
void print(std::ostream& os)
{
  os << "Type list [";
  print_impl<List>(os);
  os << "]";
}

}} // namespace blackmagic::type::ext
