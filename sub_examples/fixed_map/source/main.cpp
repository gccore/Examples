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

#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <array>

template<typename Key, typename Value, std::size_t Length>
class fixed_map final {
  using Pair_t = std::pair<Key, Value>;
  using VectorPairs_t = std::pair<std::array<Key, Length>, std::array<Value, Length>>;
  using InitializerList_t = std::initializer_list<Pair_t>;
  using Size_t = typename InitializerList_t::size_type;

  static auto constexpr init(InitializerList_t&& data) noexcept {
    VectorPairs_t result;
    for (Size_t i = 0; i < data.size(); ++i) {
      auto const ii = (data.begin() + i);
      result.first[i] = ii->first;
      result.second[i] = ii->second;
    }
    return result;
  }

 public:
  constexpr fixed_map(InitializerList_t&& data) noexcept
    : m_values(std::move(init(std::move(data)))) { }

  auto constexpr value_of(Key const& index) const {
    return find(index, m_values.first, m_values.second);
  }
  auto constexpr key_of(Value const& index) const {
    return find(index, m_values.second, m_values.first);
  }
  auto constexpr size() const noexcept {
    return m_values.first.size();
  }
  auto constexpr value_at(std::size_t const index) const {
    return m_values.second.at(index);
  }
  auto constexpr key_at(std::size_t const index) const {
    return m_values.first.at(index);
  }

 private:
  template<typename Result, typename Container1, typename Container2>
  auto constexpr find(Result const& value,
                      Container1 const& container,
                      Container2 const& container2) const {
    Size_t  index = Length + 1;

    for (Size_t i = 0; i < Length; ++i) {
      if (value == container[i]) {
        index = i;
        break;
      }
    }

    if (index == Length + 1) {
      throw std::out_of_range("Wrong Index.");
    }

    return container2[index];
  }

 private:
  VectorPairs_t const m_values;
};

int main() {
  fixed_map<std::int16_t, std::size_t, 4> constexpr test = {
    {1, 21}, {2, 17}, {3, 18}, {4, 16},
  };

  for (std::size_t i = 0; i < test.size(); ++i) {
    std::cout << test.key_of(test.value_at(i)) << ", ";
    std::cout << test.value_of(test.key_at(i)) << std::endl;
  }
}
