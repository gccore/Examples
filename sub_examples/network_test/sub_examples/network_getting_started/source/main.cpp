/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * @another_ghasem
 * g1999ramezani@gmail.com
 */

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

int main() {
  std::cout << "Hostname: " << core::util::host_name() << std::endl;

  core::config::port = 64'115;
  core::config::ip = core::constant::network::loopback;
  core::config::backlog = 5;

  std::thread(network_example::run_server).detach();
  for (auto const iterator : core::util::range<0, 10>()) {
    (void)iterator;
    network_example::run_client();
  }
}
