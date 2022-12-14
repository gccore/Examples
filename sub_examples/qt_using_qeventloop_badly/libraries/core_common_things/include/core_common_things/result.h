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

#ifndef LIBRARY_CORE_COMMON_THINGS_RESULT_H
#define LIBRARY_CORE_COMMON_THINGS_RESULT_H

#include <QString>

namespace core {
template <typename Data>
class Result {
public:
  Result(bool const state = false, QString const& message = "Nothing")
      : state(state), message(message) {
  }

  operator bool() const noexcept {
    return state;
  }

  Data data;
  bool state;
  QString message;
};
}  // namespace core

#endif  // LIBRARY_CORE_COMMON_THINGS_RESULT_H
