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

#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QWidget>
#include <QDebug>

namespace core {
void friend_slot() {
  QMessageBox::information(nullptr, "Nothing Useful", __FUNCTION__);
}

struct my_widget final: QWidget {
  friend void friend_slot();

  my_widget() : QWidget(nullptr) {
    auto const button = new QPushButton("Click ...");
    auto const layout = new QHBoxLayout;
    connect(button, &QPushButton::clicked, this, &core::friend_slot);
    layout->addWidget(button);
    setLayout(layout);
  }
};
} // namespace core

int main(int argc, char** argv) {
  QApplication application(argc, argv);
  core::my_widget widget;
  widget.show();
  return application.exec();
}
