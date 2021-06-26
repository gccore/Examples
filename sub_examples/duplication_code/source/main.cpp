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
#include <cassert>
#include <string>
#include <vector>
#include <ctime>
#include <any>

enum class type {
  string_array, integer_array
};

int int_generator() {
  return std::rand();
}
std::string string_generator() {
  return std::to_string(std::time(nullptr));
}

template<type t>
void init(std::any& value) {
  (void)value; assert(false);
}
template<>
void init<type::string_array>(std::any& value) {
  using array_t = std::vector<std::string>;
  array_t result(10);
  std::generate(std::begin(result), std::end(result), [] {
    return string_generator();
  });
  value = result;
}
template<>
void init<type::integer_array>(std::any& value) {
  using array_t = std::vector<int>;
  array_t result(10);
  std::generate(std::begin(result), std::end(result), [] {
    return int_generator();
  });
  value = result;
}

int main() {
  std::any string, integeral;
  init<type::string_array>(string);
  init<type::integer_array>(integeral);
}
