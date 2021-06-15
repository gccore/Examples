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

#include <QJsonDocument>
#include <QApplication>
#include <QVBoxLayout>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include <QTextEdit>
#include <QDialog>
#include <QString>

namespace core {
struct my_widget_2 final: QDialog {
  QTextEdit* m_json_area = nullptr;
  QTextEdit* m_parse_area = nullptr;

  explicit my_widget_2() noexcept;
  void parse_it() const noexcept;
  static constexpr auto true_string = "True";
  static constexpr auto false_string = "False";
  static constexpr auto null_string = "NULL";
  static constexpr auto undefined_string = "UNDEFINED";
  QString parse_json_array(QJsonArray const& json) const noexcept;
};
} // namespace core
