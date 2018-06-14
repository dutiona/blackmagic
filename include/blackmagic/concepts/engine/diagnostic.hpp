#pragma once

namespace blackmagic::concepts { inline namespace engine { namespace diagnostic {

template <typename Concept>
struct traits {
  template <typename... Args>
  static constexpr void diagnose();

  template <auto... Args>
  static constexpr void diagnose_v();
};

}}} // namespace blackmagic::concepts::engine::diagnostic
