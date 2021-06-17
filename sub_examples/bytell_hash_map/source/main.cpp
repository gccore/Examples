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
#include <vector>
#include <ctime>

#include <boost/timer/timer.hpp>

/*!
 * https://probablydance.com/2018/05/28/a-new-fast-hash-table-in-response-to-googles-new-fast-hash-table/
 */
#include "bytell_hash_map.hpp"

namespace core {
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

using vec_string = std::vector<std::string>;
auto generate_string_list(std::size_t const length) noexcept {
  vec_string result;
  std::generate_n(std::insert_iterator(result, std::begin(result)), length,
                  [] {return generator();});
  return result;
}
} // namespace core

int main() {
  auto const keys = core::generate_string_list(10'000'000);
  ska::bytell_hash_map<std::string, std::size_t> bytell_hash_map;

  {
    boost::timer::auto_cpu_timer insert_counter;
    (void)insert_counter;
    for (auto const& key : keys) {
      bytell_hash_map[key] = key.size();
    }
  }
  {
    auto const key = core::generator();
    boost::timer::auto_cpu_timer worst_case_find;
    (void)worst_case_find;
    for (std::size_t i = 0; i < keys.size(); ++i) {
      if (bytell_hash_map.find(key) != std::cend(bytell_hash_map)) {
        std::cout << "We find it" << std::endl;
        break;
      }
    }
  }
}
