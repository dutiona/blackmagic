#pragma once

#include "../common/utility.hpp"

namespace blackmagic::functional {

using and_t = common::all_of_v_t;

inline constexpr const and_t And{};

} // namespace blackmagic::functional::lazy
