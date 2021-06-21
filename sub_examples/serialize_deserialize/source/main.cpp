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
#include <fstream>
#include <vector>
#include <string>

namespace core {
namespace constants {
constexpr auto separator = ';';
constexpr auto newline = '\n';
constexpr auto separator_length = 1;
constexpr auto newline_length = 1;
} // namespace constants

struct serializable {
  virtual void serialize(std::string& stream) const = 0;
};

struct deserializable {
  std::size_t last_position = 0;
  virtual void deserialize(std::string const& stream) = 0;
};

namespace types {
struct record final : serializable, deserializable {
  std::uint16_t age;
  std::string name;

  void serialize(std::string& stream) const override {
    stream += std::to_string(age);
    stream += constants::separator;
    stream += name;
    stream += constants::separator;
    stream += constants::newline;
  }
  void deserialize(std::string const& stream) override {
    auto const age_position = stream.find(constants::separator, last_position);
    if (std::string::npos != age_position) {
      auto const age_string = stream.substr(last_position, age_position);
      this->age = std::uint16_t(std::stoul(age_string));
      last_position += age_position + constants::separator_length;
    }

    auto const name_position = stream.find(constants::separator, last_position);
    if (std::string::npos != name_position) {
      this->name = stream.substr(last_position, name_position);
      last_position += name_position
                       + constants::separator_length
                       + constants::newline_length;
    }
  }

};
using record_t = record;
using vec_record = std::vector<record>;

std::ostream& operator<<(std::ostream& stream, record const& input) {
  std::clog << "--------------" << std::endl;
  std::clog << "name: " << input.name << std::endl;
  std::clog << "age : " << input.age << std::endl;
  std::clog << "--------------";

  return stream;
}
} // namespace types
} // namespace core

namespace program {
static core::types::vec_record read_all_data(std::string const& file) {
  core::types::vec_record result;

  std::ifstream file_stream(file);
  if (true == file_stream.is_open()) {
    for (std::string line; std::getline(file_stream, line);) {
      core::types::record_t record;
      record.deserialize(line);
      result.push_back(std::move(record));
    }
  }

  return result;
}

static void test_program(std::string const& file) {
  core::types::record_t record_1;
  core::types::record_t record_2;

  record_1.name = "ghasem";
  record_1.age = 20;
  record_2.name = "behnam";
  record_2.age = 26;

  std::string result;
  record_1.serialize(result);
  record_2.serialize(result);

  {
    std::ofstream file_stream(file);
    if (true == file_stream.is_open()) {
      file_stream << result;
    }
    std::clog << "[" + file + "] created." << std::endl;
  }

  auto const records = read_all_data(file);
  for (auto const& record : records) {
    std::clog << record << std::endl;
  }
}
} // namespace program

int main() {
  constexpr auto file_path = "database.db";
  program::test_program(file_path);
}
