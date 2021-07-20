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

#include <QStringList>
#include <QTextStream>
#include <QString>
#include <QFile>

namespace core {
enum class open_mode {
  append, truncate
};

auto create_w_open_flags(open_mode const mode) {
  return mode == open_mode::truncate ?
         QIODevice::WriteOnly : QIODevice::WriteOnly | QIODevice::Append;
}

void write_qstringlist_to_file(QStringList const& list,
                               QString const& path,
                               open_mode const mode = open_mode::truncate) {
  QFile file(path);
  if (file.open(create_w_open_flags(mode))) {
    QTextStream stream(&file);
    for (auto const& item : list) {
      stream << item << '\n';
    }
  } else {
    throw std::runtime_error(("Couldn't open file: " + path).toStdString());
  }
}
} // namespace core

int main() {
  QStringList const list = {
    "_1", "_2", "_3", "_4"
  };
  core::write_qstringlist_to_file(list, "output.txt");
}
