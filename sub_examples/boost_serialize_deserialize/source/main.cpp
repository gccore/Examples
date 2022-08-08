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

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/deque.hpp>
//
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

struct my_structure final {
  friend class boost::serialization::access;

  std::deque<std::string> data;

  template <class Archive>
  void serialize(Archive& ar, unsigned int const) {
    ar& data;
  }
};

void save(my_structure const& obj, std::filesystem::path const& path) {
  std::ofstream output(path);
  if (!output.is_open()) {
    throw std::runtime_error("Couldn't open file: " + path.string());
  }

  boost::archive::text_oarchive boutput(output);
  boutput << obj;
}

auto load(std::filesystem::path const& path) {
  std::ifstream input(path);
  if (!input.is_open()) {
    throw std::runtime_error("Couldn't open file: " + path.string());
  }

  boost::archive::text_iarchive binput(input);
  my_structure result;
  binput >> result;
  return result;
}

int main() {
  my_structure d;
  d.data.push_back("1");
  d.data.push_back("2");
  d.data.push_back("3");

  save(d, "backup");
  auto const d2 = load("backup");

  for (auto const& item : d2.data) {
    std::cout << item << std::endl;
  }
}
