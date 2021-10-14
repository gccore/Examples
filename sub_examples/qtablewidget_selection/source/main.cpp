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

#include <QTableWidgetItem>
#include <QApplication>
#include <QTableWidget>
#include <QDebug>

void create_items(QTableWidget& table)
{
	table.setRowCount(10);
	table.setColumnCount(5);
	for (int i = 0; i < table.rowCount(); ++i)
	{
		for (int j = 0; j < table.columnCount(); ++j)
		{
			auto data = QString("%1:%2").arg(i).arg(j);
			auto item = new QTableWidgetItem(data);
			table.setItem(i, j, item);
		}
	}
}

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	QTableWidget table;
	create_items(table);
	QObject::connect(&table, &QTableWidget::cellClicked,
			 &app, [&](int const row, int const column)
	{
		Q_UNUSED(column);
		qDebug() << "---------------";
		for (int i = 0; i < table.columnCount(); ++i)
		{
			qDebug() << table.item(row, i)->data(Qt::DisplayRole).toString();
		}
		qDebug() << "---------------";
	});
	table.show();
	return app.exec();
}
