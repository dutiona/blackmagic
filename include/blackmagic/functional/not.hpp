#pragma once

#include <type_traits>

namespace blackmagic::functional {

struct not_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&& t) const
  {
    static_assert(std::is_convertible_v<T, bool>, "T must be convertible to boolean!");

    return !static_cast<bool>(std::forward<T>(t));
  }
};

inline constexpr const not_t Not{};

} // namespace blackmagic::functional
