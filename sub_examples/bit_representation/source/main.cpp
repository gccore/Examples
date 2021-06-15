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
#include <cstring>

namespace _1 {
template <typename T>
void print_bit_representation(const T value) {
  const auto bits = reinterpret_cast<const unsigned char* const>(&value);
  for (size_t i = 0; i < sizeof(value); ++i) {
    std::clog << bits[i];
  }
  std::clog << std::endl;

  const auto actual_value = *reinterpret_cast<const T* const>(bits);
  std::clog << actual_value << std::endl;
}
}

namespace _2 {
template <typename T>
void print_bit_representation(const T value) {
  unsigned char bits[sizeof(value)];
  std::memcpy(bits, &value, sizeof(value));

  for (const auto bit : bits) {
    std::clog << bit;
  }
  std::clog << std::endl;

  T actual_value;
  std::memcpy(&actual_value, bits, sizeof(value));
  std::clog << actual_value << std::endl;
}
}

struct my_struct final {
  std::string name;
  unsigned short age;
  struct {
    std::string unknown;
  } other_stuff;
};

std::ostream& operator<<(std::ostream& output, const my_struct& input) {
  output << input.name << " - ";
  output << input.age << " - [";
  output << input.other_stuff.unknown << "]";
  output << std::endl;
  return output;
}

int main() {
  const my_struct value = {"ghasem", 20, {"ramezani"}};

  std::clog << "version 1: " << std::endl;
  _1::print_bit_representation(value);

  std::clog << "--------------------" << std::endl;

  std::clog << "version 2: " << std::endl;
  _2::print_bit_representation(value);
}
