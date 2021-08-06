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
#include <sstream>
#include <string>

#include <bigint_in_one.h>

namespace core {
namespace algorithm {
auto bigint_to_string(bigint const& bn) {
  std::stringstream result;
  result << bn;
  return result.str();
}
} // namespace algorithm

namespace math {
auto factorial_of(std::size_t const n) {
  bigint const number = n;
  bigint result = 1;
  for (bigint i = 1; i <= number; i += 1) {
    result *= i;
  }
  return result;
}
} // namespace math
} // namespace core

int main() {
  std::int16_t day;
  char number;
  std::cin >> day >> number;

  auto const day_factorial = core::math::factorial_of(day);
  auto const fac_str = core::algorithm::bigint_to_string(day_factorial);
  std::cout << std::count(fac_str.cbegin(), fac_str.cend(), number) << std::endl;
}
