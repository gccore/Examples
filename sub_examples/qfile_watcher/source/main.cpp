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

#include <QFileSystemWatcher>
#include <QApplication>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QDialog>
#include <QFile>

namespace core {
struct my_widget final: QDialog {
  my_widget() {
    auto const layout = new QVBoxLayout;
    auto const text_area = new QTextEdit;
    auto const file_path = new QLineEdit;
    auto const file_watcher = new QFileSystemWatcher(this);

    text_area->setReadOnly(true);

    connect(file_path, &QLineEdit::textChanged,
    /*   */ [file_watcher](auto const& text) {
      static QString old_path;
      file_watcher->removePath(old_path);
      file_watcher->addPath(text);
      old_path = text;
    });
    connect(file_watcher, &QFileSystemWatcher::fileChanged,
    /*   */ [text_area](auto const& path) {
      QFile file(path);
      if (file.open(QIODevice::ReadOnly)) {
        text_area->setPlainText(file.readAll());
      } else {
        text_area->setPlainText("Couldn't open the file.");
      }
    });

    layout->addWidget(text_area);
    layout->addWidget(file_path);
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
