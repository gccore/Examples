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

#include "main.h"

core::my_widget_2::my_widget_2() noexcept:
  QDialog(nullptr), m_json_area(new QTextEdit),
  m_parse_area(new QTextEdit) {
  m_parse_area->setReadOnly(true);
  auto const layout = new QVBoxLayout;
  connect(m_json_area, &QTextEdit::textChanged, this, &my_widget_2::parse_it);
  layout->addWidget(m_json_area);
  layout->addWidget(m_parse_area);
  setLayout(layout);
}

void core::my_widget_2::parse_it() const noexcept {
  auto const json = QJsonDocument::fromJson(m_json_area->toPlainText().toUtf8());
  if (!json.isEmpty() && json.isArray()) {
    m_parse_area->clear();
    m_parse_area->setText(parse_json_array(json.array()));
  } else {
    m_parse_area->setText("Invalid QJsonArray");
  }
}

QString core::my_widget_2::parse_json_array(const QJsonArray& json) const noexcept {
  QString result;
  for (auto const& item : json) {
    switch (item.type()) {
      case QJsonValue::Null:
        result += null_string;
        break;
      case QJsonValue::Bool:
        result += item.toBool() ? true_string : false_string;
        break;
      case QJsonValue::Double:
        result += QString::number(item.toDouble());
        break;
      case QJsonValue::String:
        result += item.toString();
        break;
      case QJsonValue::Array:
        result += parse_json_array(item.toArray());
        break;
      case QJsonValue::Object: {
        QJsonDocument const doc(item.toObject());
        result += doc.toJson(QJsonDocument::Compact);
      } break;
      case QJsonValue::Undefined:
        result += undefined_string;
        break;
    }
    result += '\n';
  }
  return result;
}
