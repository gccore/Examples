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
 * g1999raemzani@gmail.com
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
struct my_widget final: QDialog {
  QTextEdit* m_json_area = nullptr;
  QTextEdit* m_parse_area = nullptr;

  explicit my_widget() noexcept:
    QDialog(nullptr), m_json_area(new QTextEdit),
    m_parse_area(new QTextEdit) {
    m_parse_area->setReadOnly(true);
    auto const layout = new QVBoxLayout;
    connect(m_json_area, &QTextEdit::textChanged, this, &my_widget::parse_it);
    layout->addWidget(m_json_area);
    layout->addWidget(m_parse_area);
    setLayout(layout);
  }
  void parse_it() const noexcept {
    auto const json = QJsonDocument::fromJson(m_json_area->toPlainText().toUtf8());
    if (!json.isEmpty() && json.isArray()) {
      m_parse_area->clear();
      m_parse_area->setText(parse_json_array(json.array()));
    } else {
      m_parse_area->setText("Invalid QJsonArray");
    }
  }
  static constexpr auto true_string = "True";
  static constexpr auto false_string = "False";
  static constexpr auto null_string = "NULL";
  static constexpr auto undefined_string = "UNDEFINED";
  QString parse_json_array(QJsonArray const& json) const noexcept {
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
};
} // namespace core

int main(int argc, char** argv) {
  QApplication application(argc, argv);
  core::my_widget widget;
  widget.show();
  return application.exec();
}
