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

///
/// \note Including JSON stuff.
///
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QVariant>

#include <type_traits>
#include <map>

///
/// \brief The main name-space.
///
namespace client {
///
/// \brief Contains the registered functions on the server.
///
struct functions final {
  static void f(int const _1)
  { std::printf("%d\n", _1); }

  static void f(int const _1, int const _2)
  { std::printf("%d, %d\n", _1, _2); }

  static void f(int const _1, int const _2, int const _3)
  { std::printf("%d, %d, %d\n", _1, _2, _3); }
};

///
/// \note Some typedefs for readability
///
using one_param_f = void (*)(int const);
using two_param_f = void (*)(int const, int const);
using three_param_f = void (*)(int const, int const);

///
/// \brief Contains the needed data to identifying registered functions.
///
template <typename T,
          typename = std::enable_if<std::is_pointer<T>::value>>
static constexpr std::map<unsigned, T> functions_meta = {
  {1, static_cast<one_param_f>(&functions::f)},
  {2, static_cast<two_param_f>(&functions::f)},
  {3, static_cast<three_param_f>(&functions::f)},
};

///
/// \brief This function is responsible to call the requested function.
/// \param packet : Contains the requested function.
/// \example An example of could be requested function packet schema is:
///     [
///       "par_1" : "value",
///     ]
/// And it could contains any number of parameters.
///
static void call_releated_function(QJsonArray const& packet) {
  auto const number_of_param = packet.size();
  QVariantList list_of_param;

  for (int i = 0; i < number_of_param; ++i) {
    list_of_param << packet[i].toInt(-1);
  }

  switch (number_of_param) {
    case 1:
      functions::f(list_of_param[0].toInt());
      break;
    case 2:
      functions::f(list_of_param[0].toInt(),
                   list_of_param[1].toInt());
      break;
    case 3:
      functions::f(list_of_param[0].toInt(),
                   list_of_param[1].toInt(),
                   list_of_param[2].toInt());
      break;
  }
}
}

int main() {
  QJsonArray const packet_1({12, 34});
  QJsonArray const packet_2({12, 34, 32});

  client::call_releated_function(packet_1);
  client::call_releated_function(packet_2);
}
