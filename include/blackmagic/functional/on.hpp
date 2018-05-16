#pragma once

#include <type_traits>
#include <utility>

namespace blackmagic::functional {

namespace details {

template <typename F, typename G>
class on_impl {
public:
  constexpr on_impl(F&& f, G&& g)
    : f_(std::forward<F>(f))
    , g_(std::forward<G>(g))
  {
  }

  template <typename... Args>
  constexpr decltype(auto) operator()(Args&&... args) const
  {
    return f_(g_(std::forward<Args>(args))...);
  }

private:
  const F f_;
  const G g_;
};

} // namespace details

struct on_t {
  template <typename F, typename G>
  constexpr decltype(auto) operator()(F&& f, G&& g) const
  {
    return details::on_impl<F, G>{std::forward<F>(f), std::forward<G>(g)};
  }
};

inline constexpr const on_t on{};

} // namespace blackmagic::functional
