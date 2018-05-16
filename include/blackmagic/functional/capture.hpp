#pragma once

#include "partial.hpp"

#include "../tuple/algorithm/push_front.hpp"
#include "../tuple/algorithm/unpack.hpp"

#include <utility>

namespace blackmagic::functional {

namespace tuple = blackmagic::tuple;

namespace details {

template <typename... Args>
class capture_impl {
public:
  constexpr capture_impl(Args&&... args)
    : args_(std::forward<Args>(args)...)
  {
  }

  template <typename Func>
  constexpr decltype(auto) operator()(Func&& f) const
  {
    return tuple::unpack(tuple::push_front(args_, std::forward<Func>(f)), partial);
  }

private:
  const std::tuple<Args...> args_;
};

} // namespace details

struct capture_t {
  template <typename... Args>
  constexpr decltype(auto) operator()(Args&&... args) const
  {
    return details::capture_impl(std::forward<Args>(args)...);
  }
};

inline constexpr const capture_t capture{};

} // namespace blackmagic::functional
