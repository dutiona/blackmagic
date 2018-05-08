#pragma once

namespace metaprog::concepts { inline namespace engine { namespace diagnostic {

template <typename Concept>
struct traits {
  template <typename... Args>
  static constexpr void diagnose();
};

}}} // namespace blackmagic::concepts::engine::diagnostic