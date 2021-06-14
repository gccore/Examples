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

#include <QApplication>
#include <QVBoxLayout>
#include <QStringList>
#include <QLineEdit>
#include <QSettings>
#include <QFileInfo>
#include <QVariant>
#include <QDebug>

#include <unordered_map>

namespace core {
using settings_t = std::unordered_map<QString, QVariant>;
struct widget_setting {
  virtual settings_t get() const noexcept = 0;
  virtual void set(QSettings const& values) noexcept = 0;
};

struct global_settings final {
  static inline auto setting = QSettings("my_software", "another_ghasem");

  static void path(QString const& new_path) noexcept
  { setting.setPath(QSettings::IniFormat, QSettings::UserScope, new_path); }
  static QString path(void) noexcept
  { return setting.fileName(); }
  static void commit(void) noexcept
  { setting.sync(); }

  static void append(widget_setting const* const widget) noexcept {
    for (auto const& [key, value] : widget->get()) {
      setting.setValue(key, value);
    }
  }
  static void set(widget_setting* const widget) noexcept {
    widget->set(setting);
  }
};
} // namespace core

namespace client {
struct my_widget final: QWidget, core::widget_setting {
  QLineEdit _1, _2;
  QVBoxLayout layout;

  explicit my_widget(QWidget* parent = nullptr) noexcept
    : QWidget(parent) {
    layout.addWidget(&_1);
    layout.addWidget(&_2);
    setLayout(&layout);
  }

  constexpr inline static auto _1_text_key = "my_widget/_1";
  constexpr inline static auto _2_text_key = "my_widget/_2";
  core::settings_t get() const noexcept override {
    return {
      {objectName() + _1_text_key, _1.text()},
      {objectName() + _2_text_key, _2.text()}
    };
  }
  void set(QSettings const& values) noexcept override {
    _1.setText(values.value(objectName() + _1_text_key).toString());
    _2.setText(values.value(objectName() + _2_text_key).toString());
  }
};
} // namespace client

int main(int argc, char* argv[]) {
  QApplication application(argc, argv);
  core::global_settings::path(QFileInfo(argv[0]).absolutePath() + "/config.ini");

  client::my_widget _1, _2;
  _1.setObjectName("my_widget_1");
  _2.setObjectName("my_widget_2");

  /*
   * Loads previous saved settings
   */
  core::global_settings::set(&_1);
  core::global_settings::set(&_2);

  _1.show(), _2.show();

  auto const return_value = application.exec();

  /*
   * Saves current settings
   */
  core::global_settings::append(&_1);
  core::global_settings::append(&_2);
  core::global_settings::commit();

  return return_value;
}
