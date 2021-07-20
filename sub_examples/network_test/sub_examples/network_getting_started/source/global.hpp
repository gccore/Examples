#pragma once

#include <cstdint>
#include <string>

#include "constant.h"

namespace core::config {
std::uint16_t port = 64'000;
std::string ip = constant::network::loopback;
int backlog;
} // namespace core::config
