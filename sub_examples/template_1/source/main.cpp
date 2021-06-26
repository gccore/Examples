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

#include <unordered_map>
#include <type_traits>
#include <algorithm>
#include <iostream>
#include <random>
#include <limits>
#include <vector>
#include <string>
#include <any>

namespace core {
struct parameter final {
  using list = std::vector<parameter>;

  enum class type {
    integer, string,
    integer_array, string_array,
    unknown
  };
  type t = type::unknown;
  std::any d;

  parameter(type const t_) : t(t_) {}
};
} // namespace core

namespace client {
struct generator final {
  static std::string string_generator(std::size_t const length_limit = 20) noexcept {
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
  static int number_generator(int const min = std::numeric_limits<int>::lowest(),
                              int const max = std::numeric_limits<int>::max()) noexcept {
    static std::random_device random_device;
    static std::mt19937_64 m19937(random_device());
    static std::uniform_int_distribution<int> distribution(min, max);
    return distribution(m19937);
  }

  struct constant {
    static inline auto constexpr limits = 2ULL;
  };

  static void string_type(core::parameter& parameter) noexcept {
    parameter.d = string_generator();
  }
  static void number_type(core::parameter& parameter) noexcept {
    parameter.d = number_generator();
  }
  static void string_array_type(core::parameter& parameter) noexcept {
    using array_type_t = std::vector<std::string>;
    array_type_t result(constant::limits);
    std::generate(std::begin(result), std::end(result), [] {return string_generator();});
    parameter.d = result;
  }
  static void number_array_type(core::parameter& parameter) noexcept {
    using array_type_t = std::vector<int>;
    array_type_t result(constant::limits);
    std::generate(std::begin(result), std::end(result), [] {return number_generator();});
    parameter.d = result;
  }

  static void init(core::parameter& parameter) noexcept {
    try { map.at(parameter.t)(parameter); } catch (...) { }
  }

  using function_t = void (*)(core::parameter&);
  using gen_map_t = std::unordered_map<core::parameter::type, function_t>;
  static inline gen_map_t const map = {
    {core::parameter::type::integer, &number_type},
    {core::parameter::type::string, &string_type},
    {core::parameter::type::string_array, &string_array_type},
    {core::parameter::type::integer_array, &number_array_type},
    {core::parameter::type::unknown, nullptr},
  };
};
struct print final {
  using enum_param_map_t = std::unordered_map<core::parameter::type, char const* const>;
  static inline enum_param_map_t const map = {
    {core::parameter::type::integer, "Integer"},
    {core::parameter::type::integer_array, "Integer Array"},
    {core::parameter::type::string, "String"},
    {core::parameter::type::string_array, "String Array"},
    {core::parameter::type::unknown, "Unknown"},
  };

  template<typename Type>
  static std::string to_string(Type const& value) noexcept {
    return std::to_string(value);
  }
  static std::string to_string(std::string const& value) noexcept {
    return value;
  }

  template<typename Type>
  static std::string array(core::parameter const& parameter) noexcept {
    using array_type = std::vector<Type>;
    std::string result;
    auto const data = std::any_cast<array_type>(parameter.d);
    for (auto const& item : data) {
      result += to_string(item) + ", ";
    }
    return result;
  }
  static std::string type(core::parameter const& parameter) noexcept try {
    std::string result;
    switch (parameter.t) {
      case core::parameter::type::integer:
        result = std::to_string(std::any_cast<int>(parameter.d));
        break;
      case core::parameter::type::string:
        result = std::any_cast<std::string>(parameter.d);
        break;
      case core::parameter::type::integer_array:
        result = array<int>(parameter);
        break;
      case core::parameter::type::string_array:
        result = array<std::string>(parameter);
        break;
      case core::parameter::type::unknown:
        result = "UNKNOWN";
        break;
    }
    return result;
  } catch (...) {return std::string("Broken");}
  static void it(core::parameter const& parameter) noexcept {
    std::cout << "----------------------" << std::endl;
    try {
      std::cout << "Type: " << map.at(parameter.t) << std::endl;
    } catch (...) { std::cout << "Type: Broken." << std::endl; }
    std::cout << "Value: " << type(parameter) << std::endl;
    std::cout << "----------------------" << std::endl;
  }
};
} // namespace client

int main() {
  core::parameter::list params = {
    core::parameter(core::parameter::type::integer),
    core::parameter(core::parameter::type::string),
    core::parameter(core::parameter::type::integer_array),
    core::parameter(core::parameter::type::string_array),
  };

  for (auto& param : params) {
    client::generator::init(param);
  }
  for (auto& param : params) {
    client::print::it(param);
  }
}
