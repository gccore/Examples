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
#include <numeric>
#include <vector>
#include <memory>

#include "gmpxx.h"

namespace core
{
static mpz_class convert_to_i(std::vector<std::size_t> const& vec)
{
        std::string sum;
        for (auto const number : vec) {
                sum += std::to_string(number);
        }
        return mpz_class(sum.c_str());
}
} // namespace core

static std::ostream& operator<<(std::ostream& out, mpz_class const& in)
{
        return out << in.get_str();
}

int main()
{
        std::vector<std::size_t> const vec = {
                16377,
                2631694347470643681,
                1173029487328219238
        };
        std::cout << core::convert_to_i(vec) << std::endl;
}
