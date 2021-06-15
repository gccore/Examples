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

#define LOG() \
  std::clog << counter++ << " : " << __PRETTY_FUNCTION__ << std::endl
#define LOG2() \
  std::clog << --counter << " : " << __PRETTY_FUNCTION__ << std::endl;

struct var_t final {
  static inline std::size_t counter = 1;

  var_t() {LOG();}
  ~var_t() {LOG2();}
  var_t(var_t&&) {LOG();}
  var_t(var_t const&) {LOG();}
  var_t& operator=(var_t&&) {LOG(); return *this;}
  var_t& operator=(var_t const&) {LOG(); return *this;}
};

struct use_var final {
  var_t _1, _2, _3;
};

int main() {
  use_var a;
}
