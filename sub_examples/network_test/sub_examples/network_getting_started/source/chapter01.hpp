#pragma once

#include <iostream>
#include <mutex>

#include "csocket.hpp"
#include "global.hpp"
#include "constant.h"
#include "utility.h"

namespace threading {
class cout final {
 private:
  std::mutex cout_lock;

 public:
  void lock() {
    cout_lock.lock();
  }
  ~cout() {
    cout_lock.unlock();
  }
};
} // namespace threading

namespace network_example {
void run_server() noexcept {
  try {
    core::socket socket;
    socket.echo_message() = "Ghasem is right here";
    socket.bind().listen().run();
  } catch (std::exception& exception) {
    threading::cout().lock();
    std::cerr << exception.what() << std::endl;
  }
}
void run_client() noexcept {
  try {
    core::socket socket(core::socket::socket_type::client);
    socket.connect().read(256);
    std::cout << socket.buffer() << std::endl;
  } catch (std::exception& exception) {
    threading::cout().lock();
    std::cerr << exception.what() << std::endl;
  }
}
} // namespace natwork_example

namespace chapter_01 {
void run() noexcept {
  std::cout << "Hostname: " << core::util::host_name() << std::endl;

  core::config::port = 64'145;
  core::config::ip = core::constant::network::loopback;
  core::config::backlog = 5;

  std::thread(network_example::run_server).detach();
  core::util::repeat_for<10>(network_example::run_client);
}
} // namespace chapter_01
