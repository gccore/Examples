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

#include <filesystem>
#include <iostream>
#include <fstream>

#include "json.hpp"

namespace core {
/*!
 * This is my structure json schema:
 *   {
 *     "first_name": "another-ghasem",
 *     "last_name": "another-ghasem last name",
 *     "id": "some324234id",
 *     "grade": 324.43
 *   }
 */
struct student_t final {
  std::string first_name;
  std::string last_name;
  std::string id;
  double grade;

  friend std::ostream& operator<<(std::ostream& output, student_t const& input) {
    output << "first name: " << input.first_name << std::endl;
    output << "last name: " << input.last_name << std::endl;
    output << "id: " << input.id << std::endl;
    output << "grade: " << input.grade << std::endl;
    return output;
  }
};

/*!
 * We will use this constants in JSON
 * serialization and deserialization.
 */
namespace constants {
auto constexpr first_name = "first_name";
auto constexpr last_name = "last_name";
auto constexpr id = "id";
auto constexpr grade = "grade";
} // namespace constants

auto serialize_student(student_t const& student) {
  nlohmann::json result;
  result[constants::first_name] = student.first_name;
  result[constants::last_name] = student.last_name;
  result[constants::id] = student.id;
  result[constants::grade] = student.grade;
  return result;
}

/*!
 * \brief Reads and parse the file
 * \param path: It's contains a vaild path to the json file.
 */
auto read_json(std::filesystem::path const& path) {
  if (!std::filesystem::exists(path)) {
    throw std::runtime_error("File Not Fould.");
  }

  std::ifstream file(path);
  student_t result;
  if (file.is_open()) {
    auto const json = nlohmann::json::parse(file);
    result.first_name = json[constants::first_name].get<std::string>();
    result.last_name = json[constants::last_name].get<std::string>();
    result.grade = json[constants::grade].get<double>();
    result.id = json[constants::id].get<std::string>();
  } else {
    throw std::runtime_error("Couldn't read the file.");
  }

  return result;
}

/*!
 * \brief Writes the \p json into \p path
 * \param json
 * \param path
 */
void write_json(nlohmann::json const& json, std::filesystem::path const& path) {
  if (std::filesystem::exists(path)) {
    std::cerr << "The " << path << " exists, we will override it." << std::endl;
  }

  std::ofstream file(path);
  if (file.is_open()) {
    file << json;
  } else {
    throw std::runtime_error("Couldn't open the file.");
  }
}
} // namespace core

int main() {
  core::student_t student;

  student.first_name = "ghasem";
  student.last_name = "ramezani";
  student.id = "some_id";
  student.grade = static_cast<double>(std::rand());

  auto constexpr student_file = "student.json";

  auto const json = core::serialize_student(student);
  core::write_json(json, student_file);

  auto const new_student = core::read_json(student_file);
  std::cout << new_student << std::endl;
}
