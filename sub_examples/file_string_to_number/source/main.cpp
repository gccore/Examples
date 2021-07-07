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
#include <fstream>
#include <vector>
#include <string>

namespace core::constant {
auto constexpr temp_path = "./tmp.txt";
auto constexpr number_length = 50ULL;
auto constexpr max_random_length = 100;
} // namespace core::constant

namespace core {
using vec_int = std::vector<int>;
using vec_string = std::vector<std::string>;

int generate_number() {
  return std::rand() % constant::max_random_length;
}

vec_int list_number(std::size_t const length) {
  vec_int result(length);
  std::generate(result.begin(), result.end(), generate_number);
  return result;
}

void generate_random_file(std::string const& path, std::size_t const length) {
  std::ofstream file(path);
  for (auto const number : list_number(length)) {
    file << number << '\n';
  }
  file << std::endl;
}

vec_string read_file(std::string const& path) {
  std::ifstream file(path);
  vec_string result;
  for (std::string line; std::getline(file, line);) {
    result.emplace_back(line);
  }
  return result;
}

struct convertor_v1_t {} convertor_v1;
struct convertor_v2_t {} convertor_v2;

int convert_string_to_int(std::string const& number, convertor_v1_t) {
  int result;
  std::istringstream stream(number);
  stream >> result;
  return result;
}

int convert_string_to_int(std::string const& number, convertor_v2_t) {
  return std::stoi(number);
}

template <typename Mode>
vec_int convert_list_to_int(vec_string const& list, Mode mode) {
  vec_int result;
  for (auto const& number : list) {
    try {
      result.push_back(convert_string_to_int(number, mode));
    } catch (...) {}
  }
  return result;
}
} // namespace core

int main() {
  core::generate_random_file(core::constant::temp_path, core::constant::number_length);
  auto const str_number_list = core::read_file(core::constant::temp_path);
  auto const number_list = core::convert_list_to_int(str_number_list, core::convertor_v1);

  for (auto const number : number_list) {
    std::cout << number << '\t';
  }
  std::cout << std::endl;
}
