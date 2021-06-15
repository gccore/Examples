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

#include <algorithm>
#include <iostream>
#include <string>
#include <ctime>

auto generator(std::size_t const length_limit = 20) noexcept {
  static constexpr auto rand_char_limit = 25;
  static constexpr auto first_capital_char = 65;
  static constexpr auto first_lowercase_char = 97;

  std::string random_string;
  random_string.resize(std::rand() % length_limit + length_limit / 3);

  std::generate(std::begin(random_string), std::end(random_string), [] {
    return char((std::rand() % rand_char_limit) +
                (std::rand() % 2 == 1 ? first_capital_char : first_lowercase_char));
  });
  return random_string;
}

int main() {
  std::srand(std::time(nullptr));

  std::clog << generator() << std::endl;
  std::clog << generator() << std::endl;
  std::clog << generator() << std::endl;
  std::clog << generator() << std::endl;
}
