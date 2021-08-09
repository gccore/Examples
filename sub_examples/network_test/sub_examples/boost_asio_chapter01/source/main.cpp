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

#include <boost/asio.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

namespace config {
auto constexpr ip = "127.0.0.1";
auto constexpr port = 54321ULL;
} // namespace config

namespace core::util {
auto create_address(std::string const& ip) {
  boost::system::error_code error_check;
  auto const address = boost::asio::ip::address::from_string(ip, error_check);
  if (error_check.failed()) {
    std::stringstream message;
    message << "Failed to parse IP: " << config::ip << std::endl;
    message << "Error Code: " << error_check.message() << std::endl;
    throw std::runtime_error(message.str());
  }
  return address;
}
} // namespace core::util

namespace server {
void setup_connection() {
  auto const address = boost::asio::ip::address_v6::any();
  auto const endpoint = boost::asio::ip::tcp::endpoint(address, config::port);

  boost::asio::io_service main_loop;
  auto const protocol = boost::asio::ip::tcp::v4();
  boost::asio::ip::tcp::socket socket(main_loop);

  boost::system::error_code error_check;
  socket.open(protocol, error_check);
  if (error_check.failed()) {
    std::stringstream message;
    message << "Failed to open socket: " << config::port << std::endl;
    message << "Error Message: " << error_check.message() << std::endl;
    throw std::runtime_error(message.str());
  }


}
} // namespace server

namespace client {
void setup_connection() {
  boost::asio::ip::tcp::endpoint endpoint(core::util::create_address(config::ip),
                                          config::port);
}
} // namespace client

int main() {
  std::thread _1(server::setup_connection);
  std::thread _2(client::setup_connection);

  _1.join();
  _2.join();
}
