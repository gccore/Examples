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
#include <QMessageBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QToolBox>
#include <QString>
#include <QAction>
#include <QWidget>

int main(int argc, char* argv[]) {
  QApplication event_loop(argc, argv);
  QPushButton dummy_action("test action");
  QHBoxLayout main_layout;
  QHBoxLayout tab_layout;
  QTabWidget tab_widget;
  QToolBox tool_box;
  QWidget window;

  constexpr auto tool_box_name = "toolbox_object";
  tool_box.setObjectName(tool_box_name);
  tool_box.addItem(&dummy_action, "Tools");

  tab_widget.addTab(&tool_box, "Test");
  tab_layout.addLayout(&tab_layout);
  main_layout.addWidget(&tab_widget);
  window.setLayout(&main_layout);

  QObject::connect(&dummy_action, &QPushButton::clicked, &event_loop,
  [&tab_widget] {
    if (not tab_widget.findChildren<QToolBox*>(tool_box_name).empty()) {
      QMessageBox::information(nullptr, "Information", "We find it.");
    }
  });

  window.show();
  return event_loop.exec();
}
