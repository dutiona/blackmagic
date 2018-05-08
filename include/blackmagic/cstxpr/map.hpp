#pragma once

#include "algorithm.hpp"

#include <array>
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <utility>

namespace blackmagic::cstxpr {

template <typename Key, typename Value, size_t Size = 5, typename Compare = std::equal_to<Key>>
class map {
public:
  constexpr auto begin() const
  {
    return m_data.begin();
  }
  constexpr auto begin()
  {
    return m_data.begin();
  }

  // We would have prefered to use `std::next`, however it does not seem
  // to be enabled for cstxpr use for std::array in this version
  // of gcc. TODO: reevaluate this
  constexpr auto end() const
  {
    return m_data.begin() + m_size;
  }
  constexpr auto end()
  {
    return m_data.begin() + m_size;
  }

  constexpr auto cbegin() const
  {
    return m_data.begin();
  }
  constexpr auto cend() const
  {
    return m_data.begin() + m_size;
  }

  constexpr auto find(const Key& k)
  {
    return find_impl(*this, k);
  }

  constexpr auto find(const Key& k) const
  {
    return find_impl(*this, k);
  }

  constexpr const Value& at(const Key& k) const
  {
    const auto itr = find(k);
    if (itr != end()) {
      return itr->second;
    }
    throw std::range_error("Key not found");
  }

  constexpr Value& operator[](const Key& k)
  {
    const auto itr = find(k);
    if (itr == end()) {
      auto& data = m_data[m_size++];
      data.first = k;
      return data.second;
    }
    return itr->second;
  }

  constexpr auto size() const
  {
    return m_size;
  }
  constexpr auto empty() const
  {
    return m_size == 0;
  }

private:
  template <typename This>
  static constexpr auto find_impl(This&& t, const Key& k)
  {
    return cstxpr::find_if(t.begin(), t.end(), [&k](const auto& d) { return Compare{}(d.first, k); });
  }

  std::array<std::pair<Key, Value>, Size> m_data{}; // for cstxpr use, the std::array must be initialized
  size_t                                  m_size{0};
};

} // namespace blackmagic::cstxpr
