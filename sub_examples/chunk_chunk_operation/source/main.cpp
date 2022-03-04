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
#include <iostream>
#include <numeric>
#include <vector>
#include <array>

template <typename Container, typename Operator>
void ChunkOperations(Container&& container, std::size_t const chunk, Operator const operate) {
  using ElementType =
      typename std::remove_all_extents_t<std::remove_reference_t<Container>>::value_type;
  for (std::size_t index = 0; index < container.size(); index += chunk) {
    std::vector<ElementType> chunk_list(chunk);
    for (std::size_t chunk_index = index;
         chunk_index < index + chunk && chunk_index < container.size();
         ++chunk_index) {
      chunk_list.emplace_back(container[chunk_index]);
    }
    operate(chunk_list);
  }
}

int main() {
  auto print_sum_of_anything = [](auto&& list) {
    using ElementType =
        typename std::remove_all_extents_t<std::remove_reference_t<decltype(list)>>::value_type;
    std::cout << std::accumulate(list.begin(), list.end(), ElementType{}) << std::endl;
  };
  {
    std::array list = {1, 2, 3, 4, 5, 6, 7};
    ChunkOperations(list, 3, print_sum_of_anything);
  }
  {
    std::vector<std::string> list = {"ghasem", "javad", "parisa", "iman"};
    ChunkOperations(list, 2, print_sum_of_anything);
  }
}
