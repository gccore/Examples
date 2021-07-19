#pragma once

extern "C" {
#include <sys/socket.h>
}

namespace core::constant {
namespace socket {
auto constexpr protocol = 0;
auto constexpr domain = AF_INET;
auto constexpr type = SOCK_STREAM;
auto constexpr error = -1;
auto constexpr bind_success = 0;
} // namespace socket
} // namespace core::constant
