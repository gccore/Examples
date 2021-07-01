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

#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QApplication>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDialog>
#include <QLabel>

namespace core {
struct my_widget final: QDialog {
  std::unique_ptr<QStandardItemModel> const numbers_model;
  std::unique_ptr<QStandardItemModel> const names_model;
  std::unique_ptr<QSortFilterProxyModel> const numbers_proxy;
  std::unique_ptr<QSortFilterProxyModel> const names_proxy;

  my_widget()
    : QDialog(nullptr),
      numbers_model(new QStandardItemModel),
      names_model(new QStandardItemModel),
      numbers_proxy(new QSortFilterProxyModel),
      names_proxy(new QSortFilterProxyModel) {
    auto const numbers = new QListView;
    auto const names = new QListView;
    auto const numbers_search = new QLineEdit;
    auto const names_search = new QLineEdit;
    auto const layout_1 = new QVBoxLayout;
    layout_1->addWidget(numbers);
    layout_1->addWidget(numbers_search);
    auto const layout_2 = new QVBoxLayout;
    layout_2->addWidget(names);
    layout_2->addWidget(names_search);
    auto const main_layout = new QHBoxLayout;
    main_layout->addLayout(layout_1);
    main_layout->addLayout(layout_2);
    setLayout(main_layout);

    numbers_model->appendRow(new QStandardItem("1"));
    numbers_model->appendRow(new QStandardItem("2"));
    numbers_model->appendRow(new QStandardItem("3"));
    numbers_model->appendRow(new QStandardItem("4"));
    names_model->appendRow(new QStandardItem("amir"));
    names_model->appendRow(new QStandardItem("another-amir"));
    names_model->appendRow(new QStandardItem("ghasem"));
    names_model->appendRow(new QStandardItem("another-ghasem"));

    numbers_proxy->setSourceModel(numbers_model.get());
    numbers_proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    numbers->setModel(numbers_proxy.get());
    names_proxy->setSourceModel(names_model.get());
    names_proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    names->setModel(names_proxy.get());

    connect(numbers_search, &QLineEdit::textChanged, [this](auto const value) {
      numbers_proxy->setFilterRegularExpression(value);
    });
    connect(names_search, &QLineEdit::textChanged, [this](auto const value) {
      names_proxy->setFilterFixedString(value);
    });
  }
};
} // namespace core

int main(int argc, char* argv[]) {
  QApplication application(argc, argv);
  core::my_widget widget;
  widget.show();
  return application.exec();
}
