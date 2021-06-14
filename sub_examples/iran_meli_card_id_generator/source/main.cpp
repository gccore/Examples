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
#include <string>
#include <limits>

/*!
 * NOTE: from: http://www.aliarash.com/article/codemeli/codemeli.htm
 */

namespace core {
int validate_meli_id(std::string const& input) {
  int sum = 0;
  short int value = 10;
  int result = sum % 11;

  for (size_t i = 0; i < input.length() - 1 ; i++) {
    sum += (static_cast<int>(input.at(i)) - 48) * value;
    value--;
  }

  if ((result > 2) && ((static_cast<int>(input.at(9)) - 48) == result)) {
    return 0;
  } else if ((static_cast<int>(input.at(9)) - 48) == (11 - result)) {
    return 0;
  } else {
    return -1;
  }
  return -3;
}
} // namespace core

int main() {
  for (std::size_t i = 1000000000; i < std::numeric_limits<std::size_t>::max(); ++i) {
    if (core::validate_meli_id(std::to_string(i)) == 0) {
      std::cout << i << std::endl;
    }
  }
}
