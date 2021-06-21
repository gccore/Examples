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
#include <iostream>

struct sudoku final {
  using number_t = size_t;
  struct point_t final {
    number_t x;
    number_t y;
  };

  enum class side_t {
    left_up, center_up, right_up,
    center_left, center, center_right,
    left_down, center_down, right_down,
    unknown
  };

  enum {
    wrong_index = 0
  };

  static constexpr auto limit = 9;
  number_t matrix[limit][limit] = {0};
  std::unordered_map<side_t const, point_t const> const positions = {
    {side_t::left_up, {0, 0}}, {side_t::center_up, {3, 0}}, {side_t::right_up, {6, 0}},
    {side_t::center_left, {0, 3}}, {side_t::center, {3, 3}}, {side_t::center_right, {6, 3}},
    {side_t::left_down, {0, 6}}, {side_t::center_down, {3, 6}}, {side_t::right_down, {6, 6}},
  };

  side_t which_side(point_t const& position) const {
    auto result = side_t::unknown;

    if (position.x >= 1 && position.x <= 3) {
      if (position.y >= 1 && position.y <= 3) {
        result = side_t::left_up;
      } else if (position.y >= 4 && position.y <= 6) {
        result = side_t::center_left;
      } else if (position.y >= 7 && position.y <= 9) {
        result = side_t::left_down;
      }
    } else if (position.x >= 4 && position.x <= 6) {
      if (position.y >= 1 && position.y <= 3) {
        result = side_t::center_up;
      } else if (position.y >= 4 && position.y <= 6) {
        result = side_t::center;
      } else if (position.y >= 7 && position.y <= 9) {
        result = side_t::center_down;
      }
    } else if (position.x >= 7 && position.x <= 9) {
      if (position.y >= 1 && position.y <= 3) {
        result = side_t::right_up;
      } else if (position.y >= 4 && position.y <= 6) {
        result = side_t::center_right;
      } else if (position.y >= 7 && position.y <= 9) {
        result = side_t::right_down;
      }
    }

    return result;
  }

  bool is_valid_in_row(number_t const row, number_t const value) const {
    bool result = true;

    for (number_t column = 0; column < limit; ++column) {
      if (matrix[row][column] == value) {
        result = false;
        break;
      }
    }

    return result;
  }

  bool is_valid_in_column(number_t const column, number_t const value) const {
    bool result = true;

    for (number_t row = 0; row < limit; ++row) {
      if (matrix[row][column] == value) {
        result = false;
        break;
      }
    }

    return result;
  }

  bool is_valid_in_block(point_t const& position, number_t const value) const {
    bool result = true;
    auto const side = which_side(position);

    if (side != side_t::unknown) {
      auto const start_point = positions.at(side);
      for (number_t i = start_point.x; i < (start_point.x + 3); ++i) {
        for (number_t j = start_point.y; j < (start_point.y + 3); ++j) {
          if (matrix[i][j] == value) {
            result = false;
            break;
          }
        }
      }
    }

    return result;
  }

  bool is_valid(point_t position, number_t const value) const {
    --position.x;
    --position.y;
    return is_valid_in_row(position.x, value) and
           is_valid_in_column(position.y, value) and
           is_valid_in_block(position, value);
  }

  number_t find_valid_for(point_t const& position) const {
    number_t result = wrong_index;

    for (number_t i = 1; i <= 9; ++i) {
      if (is_valid(position, i)) {
        result = i;
        break;
      }
    }

    return result;
  }

  friend std::istream& operator>>(std::istream& out, sudoku& other) {
    for (number_t i = 0; i < limit; ++i) {
      for (number_t j = 0; j < limit; ++j) {
        out >> other.matrix[i][j];
      }
    }
    return out;
  }

  friend std::istream& operator>>(std::istream& out, point_t& other) {
    out >> other.x;
    out >> other.y;
    return out;
  }
};

int main() {
  sudoku board;
  sudoku::point_t position;

  std::cin >> board;
  std::cin >> position;
  auto const valid_number = board.find_valid_for(position);

  if (valid_number != sudoku::wrong_index) {
    std::clog << valid_number << std::endl;
  } else {
    std::clog << "unknown" << std::endl;
  }
}
