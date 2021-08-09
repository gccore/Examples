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

namespace config {
auto constexpr ip = "127.0.0.1";
auto constexpr port = 54321ULL;
} // namespace config

namespace server {
void setup_connection() {
  boost::system::error_code error_check;
  auto const address = boost::asio::ip::address::from_string(config::ip, error_check);

  if (error_check.failed()) {
    std::stringstream message;
    message << "Failed to parse IP: " << config::ip << std::endl;
    message << "Error Code: " << error_check.message() << std::endl;
    throw std::runtime_error(message.str());
  }

  boost::asio::ip::tcp::endpoint endpoint(address, config::port);
}
} // namespace server

int main() {
  server::setup_connection();
}
