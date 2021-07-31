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

namespace core::constants {
auto constexpr width = 400;
auto constexpr height = 300;
auto constexpr step = 2;
} // namespace core::constants

namespace core {
struct my_widget final: QDialog {
  QPointer<QPushButton> button = nullptr;

  my_widget()
    : QDialog(nullptr),
      button(new QPushButton(this)) {
    setMinimumSize(constants::width, constants::height);
  }

  void keyPressEvent(QKeyEvent* const event) override {
    if (QKeyEvent::KeyPress == event->type()) {
      if (Qt::Key_W == event->key()) {
        button->move(button->x(), button->y() - constants::step);
      } else if (Qt::Key_S == event->key()) {
        button->move(button->x(), button->y() + constants::step);
      } else if (Qt::Key_D == event->key()) {
        button->move(button->x() + constants::step, button->y());
      } else if (Qt::Key_A == event->key()) {
        button->move(button->x() - constants::step, button->y());
      }
    }
    QDialog::keyPressEvent(event);
  }
};
} // namespace core

int main(int argc, char* argv[]) {
  QApplication application(argc, argv);
  core::my_widget widget;
  widget.show();
  return application.exec();
}
