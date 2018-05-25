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

  constexpr auto end() const
  {
    return m_data.end();
  }

  constexpr auto end()
  {
    return m_data.end();
  }

  constexpr auto cbegin() const
  {
    return m_data.cbegin();
  }

  constexpr auto cend() const
  {
    return m_data.cend();
  }

  constexpr auto rbegin() const
  {
    return m_data.rbegin();
  }

  constexpr auto rbegin()
  {
    return m_data.rbegin();
  }

  constexpr auto rend() const
  {
    return m_data.rend();
  }

  constexpr auto rend()
  {
    return m_data.rend();
  }

  constexpr auto crbegin() const
  {
    return m_data.crbegin();
  }

  constexpr auto crend() const
  {
    return m_data.crend();
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

  constexpr auto empty() const
  {
    return m_size == 0;
  }

  constexpr auto size() const
  {
    return m_size;
  }

  constexpr auto max_size() const
  {
    return Size;
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
