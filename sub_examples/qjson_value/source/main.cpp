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


  enum class array_t { } array_mode;
  enum class object_t { } object_mode;

  void parse_it() const noexcept {
    auto const json = QJsonDocument::fromJson(m_json_area->toPlainText().toUtf8());
    if (!json.isEmpty()) {
      if (json.isArray()) {
        m_parse_area->clear();
        m_parse_area->setText(parse_json(json.array(), array_mode));
      } else if (json.isObject()) {
        m_parse_area->clear();
        m_parse_area->setText(parse_json(json.object(), object_mode));
      } else {
        m_parse_area->setText("Invalid QJsonArray");
      }
    }
  }

  QString parse_json(QJsonObject const& json, object_t) const noexcept {
    QString result;
    auto const& keys = json.keys();
    for (auto const& key : keys) {
      result += key + " : " + to_string(json[key]) + "\n";
    }
    return result;
  }
  QString parse_json(QJsonArray const& json, array_t) const noexcept {
    QString result;
    for (auto const& item : json) {
      result += to_string(item) + '\n';
    }
    return result;
  }

  static auto constexpr true_string = "True";
  static auto constexpr false_string = "False";
  static auto constexpr null_string = "NULL";
  static auto constexpr undefined_string = "UNDEFINED";
  QString to_string(QJsonValue const& object) const noexcept {
    QString result;
    switch (object.type()) {
      case QJsonValue::Null:
        result += null_string;
        break;
      case QJsonValue::Bool:
        result += object.toBool() ? true_string : false_string;
        break;
      case QJsonValue::Double:
        result += QString::number(object.toDouble());
        break;
      case QJsonValue::String:
        result += object.toString();
        break;
      case QJsonValue::Array:
        result += parse_json(object.toArray(), array_mode);
        break;
      case QJsonValue::Object: {
        result += parse_json(object.toObject(), object_mode);
      } break;
      case QJsonValue::Undefined:
        result += undefined_string;
        break;
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
