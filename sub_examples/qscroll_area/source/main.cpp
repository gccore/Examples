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
#include <QScrollArea>
#include <QScrollBar>
#include <QComboBox>
#include <QPointer>
#include <QString>
#include <QDialog>

auto generator() {
  constexpr auto rand_char_limit = 25;
  constexpr auto first_capital_char = 65;
  constexpr auto rand_line_limit = 50;
  std::string random_string;

  std::generate_n(std::insert_iterator(random_string, std::begin(random_string)),
  std::rand() % rand_line_limit, [] {
    return char((std::rand() % rand_char_limit) +
                first_capital_char);
  });

  return QString::fromStdString(random_string);
}
auto create_combobox() {
  constexpr auto size = 10;

  auto const combobox = new QComboBox;
  for (int i = 0; i < size; ++i) {
    combobox->addItem(generator());
  }

  return combobox;
}

struct multi_combobox final : QWidget {
  explicit multi_combobox(int const size)
    : QWidget(nullptr),
      layout(new QVBoxLayout(this)) {
    for (int i = 0; i < size; ++i) {
      layout->addWidget(create_combobox());
    }
    setLayout(layout);
  }

  QPointer<QVBoxLayout> layout;
};

int main(int argc, char* argv[]) {
  QApplication application(argc, argv);
  auto const comboboxs = new multi_combobox(100);
  auto const scrollarea = new QScrollArea;
  auto const layout = new QVBoxLayout;
  QDialog window;

  scrollarea->setWidget(comboboxs);
  layout->addWidget(scrollarea);
  window.setLayout(layout);
  window.show();
  return application.exec();
}
