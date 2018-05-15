#pragma once

#include <tuple>
#include <type_traits>
#include <utility>

namespace blackmagic::functional {

// fwd dcl
struct partial_t {
  template <typename Func, typename... Args>
  constexpr decltype(auto) operator()(Func&& f, Args&&... args) const;
};

namespace details {

template <typename Indexes, typename Func, typename... Args>
class storage_t;

template <size_t... I, typename Func, typename... Args>
class storage_t<std::index_sequence<I...>, Func, Args...> {
public:
  constexpr storage_t(Func&& f, Args&&... args)
    : storage_(std::forward<Func>(f), std::make_tuple(std::forward<Args>(args)...))
  {
  }

  template <typename... Y>
  constexpr decltype(auto) operator()(Y&&... ys) const
  {
    return storage_.first(std::get<I>(storage_.second)..., std::forward<Y>(ys)...);
  }

private:
  const std::pair<Func, std::tuple<Args...>> storage_;
};

} // namespace details

template <typename Func, typename... Args>
constexpr decltype(auto) partial_t::operator()(Func&& f, Args&&... args) const
{
  return details::storage_t<std::index_sequence_for<Args...>, Func, Args...>(std::forward<Func>(f),
                                                                             std::forward<Args>(args)...);
}

inline constexpr const partial_t partial{};

} // namespace blackmagic::functional
