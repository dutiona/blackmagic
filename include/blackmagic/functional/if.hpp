#pragma once

#include "lazy/eval_if.hpp"
#include "lazy/make_lazy.hpp"

#include <utility>

namespace blackmagic::functional {

namespace details {

template <typename T>
class hold {
public:
  constexpr hold(T&& t) : t_(std::forward<T>(t))
  {
  }

  constexpr decltype(auto) operator()() const
  {
    return t_;
  }

private:
  T t_;
};

} // namespace details

struct if_t {
  template <typename C, typename Then, typename Else>
  constexpr decltype(auto) operator()(C&& c, Then&& then, Else&& else_) const
  {
    return lazy::eval_if(std::forward<C>(c), lazy::make_lazy(details::hold(std::forward<Then>(then))),
                         lazy::make_lazy(details::hold(std::forward<Else>(else_))));
  }
};

inline constexpr const if_t If{};

} // namespace blackmagic::functional
