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
auto constexpr empty = 0;
} // namespace socket

namespace network {
auto constexpr loopback = "127.0.0.1";
} // namespace network

namespace string {
auto constexpr nul = '\0';
} // namespace string
} // namespace core::constant
