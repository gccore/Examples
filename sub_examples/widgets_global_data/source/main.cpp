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

#include <memory>
#include <array>

#include <QApplication>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QDialog>
#include <QTimer>

namespace global {
auto constexpr length = 2ULL;
using internal_data_t = std::array<int, length>;
internal_data_t data = {1, 2};
} // namespace global

namespace core {
struct widget final: QDialog {
  widget() : QDialog(nullptr) {
    auto const _1 = new QSpinBox;
    auto const _2 = new QSpinBox;
    auto const layout = new QHBoxLayout;
    layout->addWidget(_1);
    layout->addWidget(_2);
    setLayout(layout);
    connect(_1, &QSpinBox::valueChanged, [](auto const value) {
      global::data[0] = value;
    });
    connect(_2, &QSpinBox::valueChanged, [](auto const value) {
      global::data[1] = value;
    });
    auto const timer = new QTimer(this);
    timer->setInterval(100); timer->start();
    connect(timer, &QTimer::timeout, [ = ] {
      _1->setValue(global::data[0]);
      _2->setValue(global::data[1]);
    });
  }
};
} // namespace core

int main(int argc, char* argv[]) {
  QApplication application(argc, argv);
  core::widget _1, _2, _3;
  _1.show(), _2.show(), _3.show();
  return application.exec();
}
