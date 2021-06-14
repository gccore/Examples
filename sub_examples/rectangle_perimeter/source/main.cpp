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
#include <vector>
#include <random>

namespace core {
struct rectangle {
  using vec = std::vector<rectangle>;

  double l, w;
  double perimeter() const noexcept {
    return 2 * (l + w);
  }
};

std::ostream& operator<<(std::ostream& output, rectangle const& input) {
  return output << input.l << ", " << input.w << " : " << input.perimeter();
}
} // namespace core

auto generate_random_rec(std::size_t length = 5) noexcept {
  core::rectangle::vec result;
  std::random_device random_device;
  std::mt19937_64 m19937(random_device());
  std::uniform_real_distribution<double> distribution(0.0, 5.0);
  std::generate_n(std::insert_iterator(result, std::begin(result)), length, [&] {
    return core::rectangle{distribution(m19937), distribution(m19937)};
  });
  return result;
}

int main() {
  auto recs = generate_random_rec();
  std::sort(std::begin(recs), std::end(recs), [](auto const & _1, auto const & _2) {
    return _1.perimeter() > _2.perimeter();
  });
  for (auto const& rec : recs) {
    std::cout << rec << std::endl;
  }
}
