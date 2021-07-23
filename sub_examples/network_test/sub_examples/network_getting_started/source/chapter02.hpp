#pragma once

#include <iostream>
#include <thread>
#include <mutex>

#include "chapter01.hpp"
#include "csocket.hpp"
#include "global.hpp"
#include "constant.h"
#include "utility.h"

namespace chapter_02 {
namespace network_example {
void client_test() {
  using namespace std::chrono_literals;

  static unsigned short counter = 1;
  auto const data = "Child: " + std::to_string(counter++);

  core::socket socket(core::socket::type::client);
  auto const value = socket.connect().send(data).receive(100);
  std::cout << "[C] Received value: " << value << std::endl;

  std::this_thread::sleep_for(100ms);
}
void server_test() {
  core::socket socket(core::socket::type::server);
  socket.set_option(core::socket::option::reuse_address);
  socket.bind().listen().run();
}
} // namespace network_example

void run() noexcept {
  core::config::ip = core::constant::network::loopback;
  core::config::port = 64'142;

  std::thread server(network_example::server_test);
  core::util::repeat_for<5000>(network_example::client_test);
  server.join();
}
} // namespace chapter_02
