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
#include <fstream>
#include <sstream>
#include <vector>

namespace core {
struct date_t final {
  struct date_private final {
    std::size_t year, month, day;

    date_private(std::string const& string) {
      std::stringstream stream(string);
      stream >> year >> month >> day;
    }
  };

  bool operator()(std::string const& left, std::string const& right) const {
    return compare_function(left, right);
  }

  bool compare_function(date_private const& left, date_private const& right) const  {
    bool result = false;

    if (left.year > right.year) {
      result = true;
    } else if (left.year == right.year and left.month > right.month) {
      result = true;
    } else if (left.year == right.year and left.month == right.month) {
      if (left.day > right.day) {
        result = true;
      }
    }

    return result;
  }

};
}

auto read_file(std::string const& file_name) {
  std::ifstream input_file(file_name);

  std::vector<std::string> lines;
  for (std::string line; std::getline(input_file, line);) {
    lines.emplace_back(line);
  }

  return lines;
}

int main() {
  auto lines = read_file("file");
  std::sort(std::begin(lines), std::end(lines), core::date_t());
  for (auto const& line : lines) { std::clog << line << std::endl; }
}
