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

#include <QListWidgetItem>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>

struct my_widget_t final: QWidget
{
	explicit my_widget_t(QWidget* parent = nullptr)
		: QWidget(parent)
	{
		auto const layout = new QVBoxLayout;
		layout->addWidget(new QPushButton(QString::number(std::rand())));
		layout->addWidget(new QPushButton(QString::number(std::rand())));
		setLayout(layout);
	}
};

void add_widget_item(QListWidget* const list, QWidget* const widget)
{
	auto item = new QListWidgetItem;
	item->setSizeHint(widget->sizeHint());
	list->addItem(item);
	list->setItemWidget(item, widget);
}

void create_widget_item(QListWidget* const list, std::size_t const size)
{
	for (std::size_t i = 0; i < size; ++i)
	{
		add_widget_item(list, new my_widget_t);
	}
}

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	QListWidget list;
	list.setVerticalScrollMode(QListWidget::ScrollPerPixel);
	create_widget_item(&list, 10);
	list.show();
	return app.exec();
}
