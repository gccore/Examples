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

#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "json.hpp"

namespace core::util {
auto string_generator(std::size_t const length = 10) {
  std::string result;
  for (std::size_t i = 0; i < length; ++i) {
    result += char((std::rand() % 26) + 65);
  }
  return result;
}
} // namespace core::util

namespace core::serializer {
struct serializable {
  virtual nlohmann::json serialize() const = 0;
  virtual void deserialize(nlohmann::json const& json) = 0;
};
} // namespace core::serializer

namespace core {
struct my_structure final: serializer::serializable {
  using vec = std::vector<my_structure>;

  struct keys final {
    static inline auto constexpr counter = "counter";
    static inline auto constexpr data = "data";
  };

  inline static std::uint32_t counter = 0;
  std::string data;

  static my_structure create() noexcept {
    return {};
  }

  my_structure() : data(util::string_generator()) {
    counter += 1;
  }

  nlohmann::json serialize() const override {
    nlohmann::json json;
    json[keys::counter] = counter;
    json[keys::data] = data;
    return json;
  }
  void deserialize(nlohmann::json const& json) override {
    data = json[keys::data];
  }
};

namespace serializer {
nlohmann::json serialize(my_structure::vec const& list) {
  nlohmann::json pack;
  std::for_each(std::cbegin(list), std::cend(list),
  /*         */ [&pack](auto const & item) {pack.push_back(item.serialize());});
  return pack;
}
} // namespace serializer
} // namespace core

namespace core::json::io {
void write_to_file(nlohmann::json const& json, std::string const& path) {
  std::ofstream output(path);
  std::stringstream stream(json.dump());
  output << stream.str();
}
nlohmann::json read_from_file(std::string const& path) {
  std::ifstream input(path);
  return nlohmann::json::parse(input);
}
} // namespace core::json::io

int main() {
  core::my_structure::vec data(10);
  auto const pack = core::serializer::serialize(data);
  core::json::io::write_to_file(pack, "output.txt");
}
