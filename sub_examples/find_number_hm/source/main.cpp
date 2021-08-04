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
#include <string>
#include <vector>

#include <gmp.h>

namespace core {
/*!
 * \brief Reads n number from std::cin until \p terminate given.
 * \param terminate
 * \return std::vector<int>
 */
auto read_numbers_until(int const terminate) {
  std::vector<int> numbers;
  while (true) {
    int input;
    std::cin >> input;
    if (terminate == input) {
      break;
    }
    numbers.push_back(input);
  }
  return numbers;
}

namespace algorithm {
/*!
 * \brief Finds biggest digit of \p number.
 * \param number
 * \tparam Number
 * \return Returns biggest digit.
 */
template <typename Number>
auto biggest_digit_of(Number number) noexcept {
  std::vector<Number> digits;
  while (number != 0) {
    digits.push_back(number % 10);
    number /= 10;
  }
  return *std::max_element(digits.cbegin(), digits.cend());
}
} // namespace algorithm

namespace math {
/*!
 * \brief Checks in compile time if \p number is a perfect nubmer
 * \param number
 * \tparam Number
 * \note Perfect Number: https://en.wikipedia.org/wiki/Perfect_number
 * \return Returns true in case of \p number be a perfect number
 */
template <typename Number>
constexpr bool is_perfect_number(Number const number) noexcept {
  Number sum = 0;
  for (Number i = 1; i < number; ++i) {
    if (number % i == 0) {
      sum += i;
    }
  }
  return sum == number;
}

/*!
 * \brief Checks in compile time if \p number is even.
 * \param number
 * \tparam Number
 * \return Returns true in case of \p number be even.
 */
template <typename Number>
constexpr inline bool is_even(Number const number) noexcept {
  return number % 2 == 0;
}

/*!
 * \brief Calculates factorial of \p number in compile time.
 * \param nubmer
 * \tparam Number
 * \returns Returns factorial of \p number.
 */
template <typename Number>
constexpr auto factorial_of(Number const number) noexcept {
  Number result = 1;
  for (Number i = 1; i <= number; ++i) {
    result *= i;
  }
  return result;
}

/*!
 * \brief Calculates factorial of \p number (big-int version)
 * \param number
 * \tparam Number
 * \returns Returns factorial of \p number
 */
template <typename Number>
auto bfactorial_of(Number const number) noexcept {
  mpz_t result;
  mpz_t tmp;
  mpz_init(result);
  mpz_init(tmp);
  mpz_set_ui(result, 1);
  for (Number i = 1; i <= number; ++i) {
    mpz_set_ui(tmp, i);
    mpz_mul(result, result, tmp);
  }
  std::string string;
  string.resize(mpz_sizeinbase(result, 10) + 2);
  mpz_get_str(string.data(), 10, result);
  mpz_clear(result);
  mpz_clear(tmp);
  return string;
}
} // namespace math
} // namespace core

int main() {
  auto const numbers = core::read_numbers_until(-1);
  for (auto const number : numbers) {
    if (core::math::is_even(number) &&
        core::math::is_perfect_number(number)) {
      std::cout << number << ": Is A Perfect Number, ";
      std::cout << "Factorial: " << core::math::bfactorial_of(number);
      std::cout << std::endl;
    } else {
      auto const big_dig = core::algorithm::biggest_digit_of(number);
      auto const fac = core::math::bfactorial_of(big_dig);
      std::cout << number << ": Biggest Digit: " << big_dig;
      std::cout << ", Factorial: " << fac << std::endl;
    }
  }
}
