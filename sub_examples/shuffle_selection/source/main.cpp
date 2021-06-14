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

#include <type_traits>
#include <functional>
#include <iostream>
#include <utility>
#include <random>
#include <vector>

/**
 *  @brief Randomly select an item from @p collection.
 *  @param collection: Is one of the STL collection.
 *  @param random_generator: Is a function which generate random numbers.
 *  @tparam RandomGenerator: Is a function-object.
 *  @tparam Collection<class, class>: Is the actual STL Contaier.
 *  @tparam Type: Type of each element in the container.
 *  @tparam Allocator: Usually is default allocator
 *  @return Returns a copy of selected item.
 */
template <class RandomGenerator,
          template <class, class> class Collection,
          class Type, class Allocator = std::allocator<Type>>
Type shuffle_selection(Collection<Type, Allocator> const& collection,
                       RandomGenerator random_generator) {
  static_assert(std::is_copy_assignable<Type>::value,
                "The container elements type must be copy assignable");
  static_assert(std::is_copy_constructible<Type>::value,
                "The container elements type must be copy constructible");
  static_assert(std::is_standard_layout<Collection<Type, Allocator>>::value,
                "It must be a STL Container");
  static_assert(std::is_invocable<RandomGenerator>::value,
                "RandomGenerator must be invocable");
  return collection.at(random_generator());
}

int main() {
  std::random_device random_device;
  std::mt19937_64 m19937(random_device());
  std::uniform_int_distribution<int> distribution(0, 5);
  std::vector<int> vector = {1, 2, 3, 4, 5, 6};
  std::cout << shuffle_selection(vector, std::bind(distribution, std::ref(m19937))) << std::endl;
}
