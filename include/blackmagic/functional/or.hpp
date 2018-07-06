#pragma once

#include "../common/utility.hpp"

namespace blackmagic::functional {

using or_t = common::any_of_v_t;

inline constexpr const or_t Or{};

} // namespace blackmagic::functional::lazy
