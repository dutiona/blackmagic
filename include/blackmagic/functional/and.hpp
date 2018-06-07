#pragma once

#include "../common/algorithm/all_of_v.hpp"

namespace blackmagic::functional {

using and_t = common::all_of_v_t;

inline constexpr const and_t And{};

} // namespace blackmagic::functional::lazy