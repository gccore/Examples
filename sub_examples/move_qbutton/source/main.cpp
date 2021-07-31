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
#include <QPushButton>
#include <QKeyEvent>
#include <QPointer>
#include <QDialog>

#include <bitset>

namespace core::constants {
auto constexpr width = 400;
auto constexpr height = 300;
auto constexpr step = 2;
auto constexpr super_step = 4;
auto constexpr key_length = 5;
} // namespace core::constants

namespace core::keys {
enum key_types { w, a, s, d, shift };
} // namespace core::keys

namespace core {
struct my_widget final: QDialog {
  QPointer<QPushButton> button = nullptr;
  std::bitset<constants::key_length> pressed;

  my_widget()
    : QDialog(nullptr),
      button(new QPushButton(this)) {
    setMinimumSize(constants::width, constants::height);
  }

  using key_t = int;
  void toggle_button(key_t const key, bool const state) {
    if (Qt::Key_Shift == key) {
      pressed.set(keys::shift, state);
    } else if (Qt::Key_W == key) {
      pressed.set(keys::w, state);
    } else if (Qt::Key_S == key) {
      pressed.set(keys::s, state);
    } else if (Qt::Key_D == key) {
      pressed.set(keys::d, state);
    } else if (Qt::Key_A == key) {
      pressed.set(keys::a, state);
    }
  }
  void set_pressed(key_t const key) {
    toggle_button(key, true);
  }
  void set_released(key_t const key) {
    toggle_button(key, false);
  }

  void move_button() {
    auto step = constants::step;
    if (pressed.test(keys::shift)) {
      step *= constants::super_step;
    }
    if (pressed.test(keys::w)) {
      button->move(button->x(), button->y() - step);
    }
    if (pressed.test(keys::s)) {
      button->move(button->x(), button->y() + step);
    }
    if (pressed.test(keys::d)) {
      button->move(button->x() + step, button->y());
    }
    if (pressed.test(keys::a)) {
      button->move(button->x() - step, button->y());
    }
  }

  void keyPressEvent(QKeyEvent* const event) override {
    set_pressed(event->key());
    move_button();
    QDialog::keyPressEvent(event);
  }
  void keyReleaseEvent(QKeyEvent* const event) override {
    set_released(event->key());
    move_button();
    QDialog::keyReleaseEvent(event);
  }
};
} // namespace core

int main(int argc, char* argv[]) {
  QApplication application(argc, argv);
  core::my_widget widget;
  widget.show();
  return application.exec();
}
